#pragma once

#include <iostream>
#include <queue>
#include <condition_variable>

// Enum to represent different types of market events
enum MarketEventID : int
{
    MARKET_DATA_EVENT,
    STOPPER_EVENT
};

// Struct to hold market data
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
    // Removes the first element from the queue and assigns it to the provided data reference
    void popData(MarketData& data);

    // Adds a market data event to the queue
    void sendMarketDataEvent(std::string symbol, double price, int seqNumber, int quantity);

    // Adds a stopper event to the queue to signal termination
    void enqueueStopperEvent();

private:
    std::mutex m_queueMutex; // Mutex to protect the queue
    std::condition_variable m_cv; // Condition variable for thread synchronization

    std::queue<MarketData> m_transferQueue; // Queue to hold market data events

    // Adds a generic market data event to the queue
    void pushData(const MarketData& event);
};