#pragma once
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>

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

inline double get_bitcoin_price()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl)
    {
        // 1. Updated URL with parameters
        curl_easy_setopt(curl, CURLOPT_CAINFO, "assets/ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_URL, "https://data-api.coindesk.com/index/cc/v1/latest/tick?market=ccix&instruments=BTC-USD");
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK)
        {
            // 2. The new API returns a key named "VALUE": followed by the price
            size_t pos = readBuffer.find("\"VALUE\":");
            if(pos != std::string::npos)
            {
                // Find the first digit after "VALUE":
                size_t start = readBuffer.find_first_of("0123456789", pos);
                size_t end = readBuffer.find_first_not_of("0123456789.", start);
                
                std::string price_str = readBuffer.substr(start, end - start);
                return std::stod(price_str);
            }
        }
    }
    return 0.0;
}

namespace Bitcoin {
    inline std::atomic<double> currentPrice{0.0};
    inline std::atomic<bool> isUpdating{false};

    inline void fetchBitcoinPrice()
    {
        if(isUpdating) return;
        isUpdating = true;

        std::thread worker([](){
            double price = get_bitcoin_price();
            currentPrice = price;
            isUpdating = false;
        });
        worker.detach();
    }
}