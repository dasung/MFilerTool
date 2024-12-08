#include <stdio.h>
#include <iostream>


int main( int argc, char* argv[] )
{
	DLogDebug("This is product capability to dongaLogger: INT(%d), STRING(%s) DOUBLE(%f)", 1, __PRETTY_FUNCTION__, 3.55);

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

    // Optionally suppress the window
    if (noWindow)
	{
		DLogDebug("Runing the game on supress mode!");
    }

	// Close the file
	DLogDebug("Game exit!");
    fclose(stdout);
	return 0;
}
