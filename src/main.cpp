#include <stdio.h>
#include <iostream>
#include "InputHandler.h"
#include "OutputProcessor.h"

int main( int argc, char* argv[] )
{
    LogDebug(__PRETTY_FUNCTION__);
    std::string inputFileName;

    // Check if the correct number of arguments is provided
    if (argc == 2)
    {
        inputFileName = std::string(argv[1]);
    }
    else
    {
        std::cout << "Error: This program requires exactly one argument.\n";
        std::cout << "Usage: > MFilerTool input.csv\n";
        return 1;
    }

    TransferQueue m_transferQueue;
    InputHandler inputObj(m_transferQueue);

    // Initialize the input handler with the provided file name
    if (inputObj.init(inputFileName) == false)
    {
        std::cerr << "Error: Failed to initialize InputHandler with file: " << inputFileName << "\n";
        return 1;
    }

    // Create a thread to parse the input file and produce market data
    std::thread inputThread(&InputHandler::parseInputFile, &inputObj);

    // Create a thread to process the market data and prepare the output
    OutputProcessor outputObj(m_transferQueue);
    std::thread processingThread(&OutputProcessor::populateMarketMap, &outputObj);

    inputThread.join();
    processingThread.join();

	return 0;
}
