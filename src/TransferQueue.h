#include <iostream>
#include <queue>
#include <condition_variable>

struct MarketData
{
    double price;
    int sequenceNumber;
    int quantity;
};

class TransferQueue
{
public:
    std::queue<MarketData> transferQueue;
    void pushData(const MarketData& event);
    MarketData popData();

private:
    std::mutex queue_mutex;
    std::condition_variable cv;
};