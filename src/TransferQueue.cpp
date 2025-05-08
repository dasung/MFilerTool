#include "TransferQueue.h"

void TransferQueue::pushData(const MarketData& data)
{
    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_transferQueue.push(data);
    m_cv.notify_one();
}


void TransferQueue::popData(MarketData& data)
{
    std::unique_lock<std::mutex> lock(m_queueMutex);

    // block until queue having some data in the transfer queue
    m_cv.wait(lock, [this]() { return !m_transferQueue.empty(); });

    data = m_transferQueue.front();
    m_transferQueue.pop();
}


void TransferQueue::sendMarketDataEvent(std::string symbol, double price, int seqNumber, int quantity)
{
    MarketData newDataEntity{ MARKET_DATA_EVENT, symbol, price, seqNumber, quantity};
    pushData(newDataEntity);
}

void TransferQueue::enqueueStopperEvent()
{
    MarketData stopperDataEntity{ STOPPER_EVENT, "", 0, -1, -1};
    pushData(stopperDataEntity);
}