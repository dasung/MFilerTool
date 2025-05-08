#pragma once

#include <iostream>
#include <queue>
#include <condition_variable>

#include "GenericTransferQueue.h"



class TransferQueue  : public IDataProducer, public IDataConsumer 
{
public:
    void popData(MarketData& data) override;
    void sendMarketDataEvent(std::string symbol, double price, int seqNumber, int quantity) override;
    void sendStopperEvent() override;

private:
    std::mutex m_queueMutex;
    std::condition_variable m_cv;

    std::queue<MarketData> m_transferQueue;

    void pushData(const MarketData& event);
};