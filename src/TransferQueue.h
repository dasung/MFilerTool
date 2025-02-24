#pragma once

#include <iostream>
#include <queue>
#include <condition_variable>

struct MarketData
{
    std::string symbol;
    double price;
    int sequenceNumber;
    int quantity;
};

class TransferQueue
{
public:
    std::queue<MarketData> transferQueue;
    void pushData(const MarketData& event);
    MarketData popData();
    void produceMarketData(std::string symbol, double price, int seqNumber, int quantity);

private:
    std::mutex queue_mutex;
    std::condition_variable cv;
};