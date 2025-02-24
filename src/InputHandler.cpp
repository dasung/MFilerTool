
#include "InputHandler.h"


InputHandler::InputHandler(TransferQueue& tq, std::string& fileName) : 
                            m_dataPipe(tq), m_inputFileName(fileName)
{
}


void InputHandler::parseInputFile()
{
    std::string csvLine;

    std::ifstream file(m_inputFileName);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << m_inputFileName << std::endl;
        return;
    }

    while (std::getline(file, csvLine))
    {
        std::stringstream ss(csvLine);
        std::string seqNumStr, symbolStr, priceStr, qtyStr;

        if (std::getline(ss, seqNumStr, ',') &&
            std::getline(ss, symbolStr, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, qtyStr, ','))
        {

            DataRow row;
            std::stringstream hexStream(seqNumStr);
            hexStream >> std::hex >> row.sequenceNumber; // Convert from hex

            if (hexStream.fail())
            {
                std::cerr << "Error converting seqNo: " << seqNumStr << std::endl;
                continue; // Skip the row
            }

            try
            {
                row.symbol = symbolStr;
                row.price = std::stod(priceStr);
                row.quntity = std::stoi(qtyStr);
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Error converting price or qty: " << e.what() << std::endl;
                continue;
            }

            std::cout << "SeqNumber: " << row.sequenceNumber << ", Symbol: " << row.symbol << ", Price: " << row.price << ", Qty: " << row.quntity << std::endl;
        }
    }
}

std::vector<DataRow> InputHandler::readCSV(const std::string& filename)
{
    std::vector<DataRow> data;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string seqNumStr, symbolStr, priceStr, qtyStr;

        if (std::getline(ss, seqNumStr, ',') &&
            std::getline(ss, symbolStr, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, qtyStr, ','))
        {

            DataRow row;
            std::stringstream hexStream(seqNumStr);
            hexStream >> std::hex >> row.sequenceNumber; // Convert from hex

            if (hexStream.fail()) {
                std::cerr << "Error converting seqNo: " << seqNumStr << std::endl;
                continue; // Skip the row
            }

            try
            {
                row.symbol = symbolStr;
                row.price = std::stod(priceStr);
                row.quntity = std::stoi(qtyStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error converting price or qty: " << e.what() << std::endl;
                continue;
            }

            data.push_back(row);
        }
    }

    return data;
}