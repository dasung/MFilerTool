#include <stdio.h>
#include <iostream>
#include "InputHandler.h"
#include "OutputProcessor.h"

#include "TransferQueue.h"
#include "PriorityTransferQueue.h"

int main( int argc, char* argv[] )
{
    LogDebug(__PRETTY_FUNCTION__);
    std::string inputFileName;
    if (argc == 2)
    {
        inputFileName = std::string(argv[1]);
    }
    else
    {
        std::cout << "This program takes only one argument..." << argc << "\n";
        std::cout << "Usage: > MFilerTool input.csv\n";
        return 0;
    }

    TransferQueue m_transferQueue;

    // processing thread - prepare output
    OutputProcessor outputObj(m_transferQueue);
    std::thread processingThread(&OutputProcessor::populateMarketMap, &outputObj);
    

    InputHandler inputObj(m_transferQueue);

    if (inputObj.init(inputFileName) == false)
        return 0;

    // input thread - produce market data
    std::thread inputThread(&InputHandler::parseInputFile, &inputObj);

    inputThread.join();
    processingThread.join();

	return 0;
}
