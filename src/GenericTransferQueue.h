#pragma once

#include <iostream>

enum MarketEventID : int
{
    MARKET_DATA_EVENT,
    STOPPER_EVENT
};

struct MarketData
{
    MarketEventID id;
    std::string symbol;
    double price;
    int sequenceNumber;
    int quantity;
};

// Producer Interface (for InputHandler)
class IDataProducer
{
public:
    virtual ~IDataProducer() = default;
    virtual void sendMarketDataEvent(const std::string symbol, double price, int seqNum, int qty) = 0;
    virtual void sendStopperEvent() = 0;
};
    
// Consumer Interface (for OutputProcessor)
class IDataConsumer 
{
public:
    virtual ~IDataConsumer() = default;
    virtual void popData(MarketData& data) = 0;
};