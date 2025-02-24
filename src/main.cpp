#include <stdio.h>
#include <iostream>

#include "InputHandler.h"


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

    std::cout << "hello world...\n";
    // TODO: parse cmd input
    std::string inFile = "input.csv";
    InputHandler inputObj(m_transferQueue, inFile);

    std::thread inputThread(&InputHandler::parseInputFile, &inputObj);

    inputThread.join();


    /*std::vector<DataRow> data = m_input.readCSV("input.csv");

    for (const auto& row : data)
    {
        std::cout << "SeqNumber: " << row.sequenceNumber
                  << ", Symbol: " << row.symbol
                  << ", Price: " << row.price
                  << ", Qty: " << row.quntity << std::endl;
    }*/



    //fclose(stdout);
	return 0;
}
