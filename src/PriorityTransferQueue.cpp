#include "PriorityTransferQueue.h"
#include <climits>

void PriorityTransferQueue::sendMarketDataEvent(const std::string symbol, double price, int seqNum, int qty) 
{
    LogDebug(__PRETTY_FUNCTION__);
    MarketData newDataEntity{ MARKET_DATA_EVENT, symbol, price, seqNum, qty};
    pushData(newDataEntity);
}

void PriorityTransferQueue::sendStopperEvent()
{
    LogDebug(__PRETTY_FUNCTION__);
    MarketData stopperDataEntity{ STOPPER_EVENT, "", 0, INT_MAX, -1};
    pushData(stopperDataEntity);
}

void PriorityTransferQueue::popData(MarketData& data) 
{
    LogDebug(__PRETTY_FUNCTION__);
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_cv.wait(lock, [this] { return !m_priorityQueue.empty(); });
    data = m_priorityQueue.top();
    m_priorityQueue.pop();
}

void PriorityTransferQueue::pushData(const MarketData& data)
{
    LogDebug(__PRETTY_FUNCTION__);
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_priorityQueue.push(data);
    m_cv.notify_one();
}