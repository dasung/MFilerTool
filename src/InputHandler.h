#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

#include "TransferQueue.h"

struct DataRow
{
    int sequenceNumber;
    std::string symbol;
    double price;
    int quntity;
};

class InputHandler
{
public:
    InputHandler(TransferQueue& tq);
    ~InputHandler() = default;

    bool init(std::string& fileName);
    void parseInputFile();

private:
    TransferQueue& m_dataPipeLineIn;
    std::ifstream m_inputFile;
};
