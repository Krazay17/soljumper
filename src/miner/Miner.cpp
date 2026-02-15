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
    long long thread_hashes;

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
        thread_hashes++;
        if(thread_hashes > 10000)
        {
            total_hashes += thread_hashes;
            thread_hashes = 0;
        }
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
    for (int i = 0; i < num_threads; i++)
    {
        long long offset = i * 100000000LL;
        workers.push_back(thread(&BitcoinMiner::mine_worker, this, data, offset, std::ref(result)));
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
