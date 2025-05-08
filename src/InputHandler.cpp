
#include "InputHandler.h"

InputHandler::InputHandler(TransferQueue& tq) : m_dataPipeLineIn(tq)
{
}

bool InputHandler::init(std::string& fileName)
{
    LogDebug(__PRETTY_FUNCTION__);
    m_inputFile.open(fileName);

    if (m_inputFile.is_open() == false)
    {
        std::cout << "Error: cannot open the input file - " << fileName << std::endl;
        return false;
    }

    if (m_inputFile.fail() == true)
    {
        std::cout << "Error: failed to open due to permission or availability of the input file - " << fileName << std::endl;
        return false;
    }

    return true;
}


void InputHandler::parseInputFile()
{
    LogDebug("%s - input thread started", __PRETTY_FUNCTION__);
    
    std::string csvLine;

    while (std::getline(m_inputFile, csvLine))
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

            // debug
            //std::cout << "DataPipeIn - SeqNumber: " << row.sequenceNumber << ", Symbol: " << row.symbol << ", Price: " << row.price << ", Qty: " << row.quntity << std::endl;

            m_dataPipeLineIn.sendMarketDataEvent(row.symbol, row.price, row.sequenceNumber, row.quntity);
        }
    }

    m_dataPipeLineIn.enqueueStopperEvent();
}
