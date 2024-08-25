/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* argv[] )
{
	DLogDebug("This is product capability to dongaLogger: INT(%d), STRING(%s) DOUBLE(%f)", 1, "dongaLog.txt", 3.55);

	// Redirect stdout to a file
    freopen("stdout.txt", "w", stdout);

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
		printf( "Runing the game on supress mode!\n" );
        SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    }

	//Start up SDL and create window
	if( !init(noWindow) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		printf( "Game initialized!\n" );
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			printf( "Game media loaded!\n" );
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			// Main-loop for application
			while( !quit )
			{
				// Event-loop: get most recent event from the event queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						printf( "Game terminated!\n" );
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						switch( e.key.keysym.sym )
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
				}

				//Apply the image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );

				// If --no-window is set, terminate the application after some condition
				if (noWindow)
				{
					printf( "Game delay 5s!\n" );
					SDL_Delay(5000);  // Short delay to simulate work
					quit = true;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	// Close the file
	printf( "Game exit!\n" );
    fclose(stdout);
	return 0;
}
