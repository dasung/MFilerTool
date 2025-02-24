#include <stdio.h>
#include <iostream>

#include "InputHandler.h"
#include "OutputProcessor.h"

int main( int argc, char* argv[] )
{
    // Check for --no-window argument
    bool noWindow = false;
    for (int i = 1; i < argc; ++i)
	{
        if (std::string(argv[i]) == "--no-window")
		{
            noWindow = true;
            break;
        }
    }

    // option suppress gui window
    if (noWindow)
	{
		//LogDebug("runing in the supress mode!");
    }

    TransferQueue m_transferQueue;

    // TODO: parse cmd input
    std::string inFile = "input.csv";
    InputHandler inputObj(m_transferQueue, inFile);

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
