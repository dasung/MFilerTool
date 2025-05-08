#pragma once

#include <iostream>
#include <queue>
#include <condition_variable>
#include <climits>

#include "GenericTransferQueue.h"

// Comparator for priority (e.g., prioritize lower sequence numbers)
struct PriorityComparator 
{
    bool operator()(const MarketData& a, const MarketData& b)
    {
        return a.sequenceNumber > b.sequenceNumber; // Lower seqNum first
    }
};

class PriorityTransferQueue : public IDataProducer, public IDataConsumer
{
private:
    std::priority_queue<MarketData, std::vector<MarketData>, PriorityComparator> m_priorityQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_cv;

public:
    void sendMarketDataEvent(const std::string symbol, double price, int seqNum, int qty) override;

    void sendStopperEvent() override;

    void popData(MarketData& data) override;

    void pushData(const MarketData& data);
};