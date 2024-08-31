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
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init(bool isWindowHide)
{
	DLogDebug(__PRETTY_FUNCTION__);
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		DLogDebug("SDL could not initialize! SDL_Error: %s", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			DLogDebug("Window could not be created! SDL_Error: %s", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

	return success;
}


bool loadMedia()
{
	DLogDebug(__PRETTY_FUNCTION__);
	//Loading success flag
	bool success = true;

	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_Surface* loadedSurface = SDL_LoadBMP( m_imgPath[i].c_str() );
		if( loadedSurface == NULL )
		{
			DLogDebug( "Unable to load image %s! SDL Error: %s", m_imgPath[i].c_str(), SDL_GetError());
			success = false;
			break;
		}

		gKeyPressSurfaces[ i ] = loadedSurface;
		DLogDebug("Image loaded sucessfully... %s", m_imgPath[i].c_str());
	}

	return success;
}


void close()
{
	DLogDebug(__PRETTY_FUNCTION__);
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

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
        SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    }

	//Start up SDL and create window
	if( !init(noWindow) )
	{
		DLogDebug("Failed to initialize!");
	}
	else
	{
		DLogDebug("Game initialized!");
		//Load media
		if( !loadMedia() )
		{
			DLogDebug("Failed to load media!" );
		}
		else
		{
			DLogDebug("Game media loaded!");
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
						DLogDebug("Game terminated!");
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
					DLogDebug("Game delay 5s!");
					SDL_Delay(5000);  // Short delay to simulate work
					quit = true;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	// Close the file
	DLogDebug("Game exit!");
    fclose(stdout);
	return 0;
}
