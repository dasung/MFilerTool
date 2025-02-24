#pragma once

#include <iostream>
#include <queue>
#include <condition_variable>


enum MarketEventID : int
{
    MARKET_DATA_EVENT,
    STOPPER_EVENT
};

struct MarketData
{
    MarketEventID id;
    std::string symbol;
    double price;
    int sequenceNumber;
    int quantity;
};

class TransferQueue
{
public:
    void popData(MarketData& data);
    void sendMarketDataEvent(std::string symbol, double price, int seqNumber, int quantity);
    void sendStopperEvent();

private:
    std::mutex m_queueMutex;
    std::condition_variable m_cv;

    std::queue<MarketData> m_transferQueue;

    void pushData(const MarketData& event);
};