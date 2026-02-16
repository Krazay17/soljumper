#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <asio.hpp>
#include <asio/ssl.hpp>

inline void logToFile(std::string message)
{
    std::ofstream logfile;
    logfile.open("sol_log.txt", std::ios_base::app);
    if(logfile.is_open())
    {
        logfile << message <<std::endl;
        logfile.close();
    }
}

inline size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

namespace Bitcoin {
    inline std::atomic<double> currentPrice{0.0};
    inline std::atomic<bool> isUpdating{false};

    inline double get_price_ssl() {
        try {
            asio::io_context io;
            // 1. Create SSL Context (Standard for clients)
            asio::ssl::context ctx(asio::ssl::context::sslv23);
            ctx.set_default_verify_paths();

            asio::ip::tcp::resolver resolver(io);
            auto endpoints = resolver.resolve("data-api.coindesk.com", "443");

            // 2. Wrap a standard socket in an SSL stream
            asio::ssl::stream<asio::ip::tcp::socket> socket(io, ctx);
            asio::connect(socket.lowest_layer(), endpoints);
            
            // 3. Perform the SSL handshake
            socket.handshake(asio::ssl::stream_base::client);

            std::string request = 
                "GET /index/cc/v1/latest/tick?market=ccix&instruments=BTC-USD HTTP/1.1\r\n"
                "Host: data-api.coindesk.com\r\n"
                "Connection: close\r\n\r\n";

            asio::write(socket, asio::buffer(request));

            std::string response;
            asio::error_code error;
            char buf[4096];
            while (size_t len = socket.read_some(asio::buffer(buf), error)) {
                response.append(buf, len);
                if (error == asio::error::eof) break;
            }

            // Simple parsing (same as before)
            size_t pos = response.find("\"VALUE\":");
            if (pos != std::string::npos) {
                size_t start = response.find_first_of("0123456789", pos);
                size_t end = response.find_first_not_of("0123456789.", start);
                return std::stod(response.substr(start, end - start));
            }
        } catch (std::exception& e) {
            std::cerr << "SSL Error: " << e.what() << std::endl;
        }
        return 0.0;
    }

    inline void fetchBitcoinPrice() {
        if (isUpdating) return;
        isUpdating = true;
        std::thread([]() {
            currentPrice = get_price_ssl();
            isUpdating = false;
        }).detach();
    }
}