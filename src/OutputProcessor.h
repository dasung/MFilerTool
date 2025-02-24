#pragma once

#include <iostream>
#include <fstream> 
#include <set>
#include <map>

#include "TransferQueue.h"



struct MarketDataKey
{
    double price;
    int seqNum;
    int qty;
};

struct SortingOperator
{
    bool operator()(const MarketDataKey& k1, const MarketDataKey& k2) const
    {
        if (k1.price != k2.price)
            return k1.price < k2.price;  // ascending
        return k1.seqNum > k2.seqNum;   //descending
    }
};

class OutputProcessor
{
public:
    OutputProcessor(TransferQueue& tq);

    ~OutputProcessor() = default;

    void populateMarketMap();
private:
    TransferQueue& m_dataPipeLineOut;
    std::map<std::string, std::set<MarketDataKey, SortingOperator>> m_MarketDataMap;

    void insertDataToMap(std::string& symbol, const MarketDataKey& key);
    void debugMarketDataMap();

    // file write functions
    void generateOutput();
};