#include "OutputProcessor.h"


OutputProcessor::OutputProcessor(TransferQueue& tq) : m_dataPipeLineOut(tq)
{
}

void OutputProcessor::populateMarketMap()
{
    std::cout << "output thread started\n";

    while (true)
    {
        auto marketData = m_dataPipeLineOut.popData();
        std::cout << "DataPipeOut - SeqNumber: " << marketData.sequenceNumber << ", Symbol: " << marketData.symbol << ", Price: " << marketData.price << ", Qty: " << marketData.quantity << std::endl;
    }
    
}