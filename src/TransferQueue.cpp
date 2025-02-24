#include "TransferQueue.h"

void TransferQueue::pushData(const MarketData& data)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    transferQueue.push(data);
    cv.notify_one();
}


void TransferQueue::readData(MarketData& data)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (cv.wait_for(lock, std::chrono::seconds(5), [this]() { return !transferQueue.empty(); }))
    {
        data = transferQueue.front();
        transferQueue.pop();
    }
    else {
        std::cout << "popEvent timed out (queue empty)" << std::endl;
    }
}


void TransferQueue::produceMarketData(std::string symbol, double price, int seqNumber, int quantity)
{
    MarketData newData{ symbol, price, seqNumber, quantity};
    pushData(newData);
}