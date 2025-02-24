#include "TransferQueue.h"

void TransferQueue::pushData(const MarketData& event)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    transferQueue.push(event);
    cv.notify_one();
}


MarketData TransferQueue::popData()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (cv.wait_for(lock, std::chrono::seconds(5), [this]() { return !transferQueue.empty(); }))
    {
        MarketData data = transferQueue.front();
        transferQueue.pop();
        return data;
    }
    else {
        std::cout << "popEvent timed out (queue empty)" << std::endl;
        return MarketData(); // Or handle timeout appropriately
    }
}