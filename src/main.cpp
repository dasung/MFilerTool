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

    std::cout << "hello world\n";
    InputHandler input;
    input.readCSV("input.csv");

    //fclose(stdout);
	return 0;
}
