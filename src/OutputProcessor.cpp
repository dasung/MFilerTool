#include <cstdio>
#include <cstdarg>
#include <iomanip>

#include "OutputProcessor.h"

OutputProcessor::OutputProcessor(TransferQueue& tq) : m_dataPipeLineOut(tq)
{
}

void OutputProcessor::populateMarketMap()
{
    LogDebug("%s - processing thread started.", __PRETTY_FUNCTION__);
    while (true)
    {
        MarketData aDataElement;
        m_dataPipeLineOut.popData(aDataElement);
        
        // debug
        //std::cout << "DataPipeOut - SeqNumber: " << marketData.sequenceNumber << ", Symbol: " << marketData.symbol << ", Price: " << marketData.price << ", Qty: " << marketData.quantity << std::endl;
        
        if (aDataElement.id == MarketEventID::STOPPER_EVENT)
            break;
        
        insertDataToMap(aDataElement.symbol, {aDataElement.price, aDataElement.sequenceNumber, aDataElement.quantity});   
    }

    // debug
    //debugMarketDataMap();
    generateOutput();
}


void OutputProcessor::insertDataToMap(std::string& symbol, const MarketDataKey& key)
{
    auto it = m_MarketDataMap.find(symbol);
    if (it != m_MarketDataMap.end())
    {
        auto result = it->second.insert(key); // add to existing set
        if (result.second == false)
        {
            std::cout << "unexpected duplicated key was found.\n";
            return;
        }
    }
    else
    {
        m_MarketDataMap[symbol] = {key};
    }

    ++m_totalRows;
}

void OutputProcessor::generateOutput()
{
    std::cout << "Total Rows: " << m_totalRows << std::endl;
    for (const auto& [symbol, mDataSet] : m_MarketDataMap)
    {
        std::string fileName = symbol + ".csv";
        std::ofstream outFile(fileName);
        if (!outFile)
        {
            std::cerr << "Error: Could not open file for writing - " << fileName << "\n";
            return;
        }

        size_t count = 0;
        size_t dataSetSize = mDataSet.size();

        outFile << std::fixed << std::setprecision(2);

        for (const auto& key : mDataSet)
        {
            outFile <<  key.price << ",";
            outFile << key.qty << ",";
            outFile << key.seqNum;

            if (++count < dataSetSize)
                outFile << "\n";
        }

        std::cout << symbol << " Rows: " << count << std::endl;

        outFile.close();
    }
}

void OutputProcessor::debugMarketDataMap()
{
    for (const auto& [symbol, mData] : m_MarketDataMap)
    {
        std::cout << "MarketData for " << symbol << ":\n";
        for (const auto& key : mData) {
            std::cout << "  Price: " << key.price
                      << ", Qty: " << key.qty
                      << ", SeqNum: " << key.seqNum << '\n';
        }
        std::cout << '\n';
    }
}

