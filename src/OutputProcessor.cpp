#include <cstdio>
#include <cstdarg>

#include "OutputProcessor.h"

OutputProcessor::OutputProcessor(TransferQueue& tq) : m_dataPipeLineOut(tq)
{
}

void OutputProcessor::populateMarketMap()
{
    std::cout << "output thread started\n";

    // TODO: loop termination logic
    int iCount = 0;
    while (true)
    {
        if (++iCount == 11) break;

        auto marketData = m_dataPipeLineOut.popData();
        
        // debug
        //std::cout << "DataPipeOut - SeqNumber: " << marketData.sequenceNumber << ", Symbol: " << marketData.symbol << ", Price: " << marketData.price << ", Qty: " << marketData.quantity << std::endl;
       
        insertDataToMap(marketData.symbol, {marketData.price, marketData.sequenceNumber, marketData.quantity});
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
        }
    }
    else
    {
        m_MarketDataMap[symbol] = {key};
    }    
}

void OutputProcessor::generateOutput()
{
    for (const auto& [symbol, mDataSet] : m_MarketDataMap)
    {
        //TODO: handle the path
        std::string fileName = symbol + ".csv";
        std::ofstream outFile(fileName);
        if (!outFile)
        {
            std::cerr << "Error: Could not open file for writing!\n";
            return;
        }

        size_t rowCount = 0;
        size_t totalRows = mDataSet.size();

        for (const auto& key : mDataSet)
        {
            outFile << key.price << ",";
            outFile << key.qty << ",";
            outFile << key.seqNum;

            if (++rowCount < totalRows)
                outFile << "\n";
        }

        outFile.close(); // Close the file
    }
}

void OutputProcessor::debugMarketDataMap()
{
    for (const auto& [symbol, mData] : m_MarketDataMap)
    {
        std::cout << "MarketData for " << symbol << ":\n";
        for (const auto& key : mData) {
            std::cout << "  Price: " << key.price   // TODO: formatting floating 4.6 -> 4.60
                      << ", Qty: " << key.qty
                      << ", SeqNum: " << key.seqNum << '\n';
        }
        std::cout << '\n';
    }
}

