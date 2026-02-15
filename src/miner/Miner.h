#pragma once
#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include <mutex>

struct BitcoinHeader
{
    uint32_t version;
    uint8_t prev_hash[32];
    uint8_t merkle_root[32];
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;
};

struct MineResult
{
    bool found;
    std::string hash;
    uint32_t nonce;
    double time_taken;
    long long total_hashes;
};

class BitcoinMiner
{
private:
    std::atomic_bool shouldStop{false};
    std::atomic<bool> found{false};
    std::atomic<long long> total_hashes{0};
    std::vector<std::thread> workers;
    std::string target_string;
    std::mutex result_mutex;
    void mine_worker(BitcoinHeader block_to_copy, long long start_nonce, MineResult &result);

public:
    void run(BitcoinHeader data, std::string target, MineResult &result);
    long long getTotalHashes() const { return total_hashes.load(); }
    void stop();
};