#include "Miner.h"
#include "logger/Logger.h"
#include "hasher/sha256.h"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

void BitcoinMiner::mine_worker(BitcoinHeader block_to_copy, long long start_nonce, MineResult &result)
{
    SHA256 sha;
    string h;
    BitcoinHeader local_block = block_to_copy;
    local_block.nonce = start_nonce;

    const unsigned char *raw_data = reinterpret_cast<const unsigned char *>(&local_block);

    while (!found && !shouldStop)
    {
        h = sha(sha(raw_data, 80));

        if (h.substr(0, target_string.length()) == target_string)
        {
            found = true;
            std::lock_guard<std::mutex> lock(result_mutex);
            result.hash = h;
            result.nonce = local_block.nonce;
            result.total_hashes = total_hashes;
            result.found = true;
            return;
        }
        local_block.nonce++;
        total_hashes++;
    }
}

void BitcoinMiner::run(BitcoinHeader data, string target, MineResult &result)
{
    found = false;
    shouldStop = false;
    total_hashes = 0;
    target_string = target;
    workers.clear();

    int num_threads = thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 2;

    cout << "Launching " << num_threads << " mining threads"
         << "\nLooking for hash starting with: " << target_string << endl;

    auto last_time = chrono::steady_clock::now();

    for (int i = 0; i < num_threads; i++)
    {
        long long offset = i * 100000000LL;
        workers.push_back(thread(&BitcoinMiner::mine_worker, this, data, offset, std::ref(result)));
    }

    while (!found && !shouldStop)
    {
        this_thread::sleep_for(chrono::seconds(1));

        auto now = chrono::steady_clock::now();
        chrono::duration<double> delta = now - last_time;
        double seconds = delta.count();
        double hashrate = total_hashes / seconds;
        if (!found)
            cout << "\rSpeed: " << fixed << setprecision(2) << (hashrate / 1000.0) << " KH/s | "
                 << "Total Hashes: " << total_hashes << flush;
    }

    for (auto &t : workers)
    {
        if (t.joinable())
            t.join();
    }
}

void BitcoinMiner::stop()
{
    shouldStop = true;

    for (auto &t : workers)
    {
        if (t.joinable())
            t.join();
    };
    workers.clear();
}
