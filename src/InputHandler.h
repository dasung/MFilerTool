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
    InputHandler(TransferQueue& tq, std::string& fileName);
    ~InputHandler() = default;

    void parseInputFile();
    std::vector<DataRow> readCSV(const std::string& filename);

private:
    TransferQueue& m_dataPipeLineIn;
    std::string m_inputFileName;
};
