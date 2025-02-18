#include <stdio.h>
#include <iostream>

int main( int argc, char* argv[] )
{
	LogDebug(__PRETTY_FUNCTION__);

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
		LogDebug("runing in the supress mode!");
    }

    fclose(stdout);
	return 0;
}
