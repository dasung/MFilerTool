#pragma once

#include <iostream>

#include "TransferQueue.h"

class OutputProcessor
{
public:
    OutputProcessor(TransferQueue& tq);

    ~OutputProcessor() = default;

    void populateMarketMap();
private:
    TransferQueue& m_dataPipeLineOut;
};