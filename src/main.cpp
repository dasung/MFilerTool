#include <stdio.h>
#include <iostream>

#include "InputHandler.h"
#include "OutputProcessor.h"

int main( int argc, char* argv[] )
{
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
    InputHandler inputObj(m_transferQueue);

    if (inputObj.init(inputFileName) == false)
        return 0;

    // input thread - produce market data
    std::thread inputThread(&InputHandler::parseInputFile, &inputObj);

    // processing thread - prepare output
    OutputProcessor outputObj(m_transferQueue);
    std::thread processingThread(&OutputProcessor::populateMarketMap, &outputObj);

    inputThread.join();
    processingThread.join();


    //fclose(stdout);
	return 0;
}
