#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>

// Include Windows //

void drawMultipleRect(SDL_Surface* bmp,SDL_Surface* screen,SDL_Rect *dstrectTab, int nbRect)
{
    int i;
    SDL_Rect dstrect;
    for(i=0;i<nbRect;i++)
    {
        dstrect = (SDL_Rect) dstrectTab[i];
        SDL_BlitSurface(bmp, 0, screen, &dstrect);
    }

}

void rectDirAlloc(SDL_Rect *dstrectTab, int **tabDir, int nbRect)
{
    int i,j;
    for(i=0;i<nbRect;i++)
    {
        dstrectTab[i].x = rand()%500;
        dstrectTab[i].y = rand()%350;
        tabDir[i] = (int*) calloc (2,sizeof(int));
    }

    for(i=0;i<nbRect;i++)
    {
        for(j=0;j<2;j++)
        {
            tabDir[i][j] = 1;
        }

    }

}

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    int sWidth=640, sHeigth=320;
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(sWidth, sHeigth, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen

    srand(time(NULL));
    int nbRect = 20,i;
    SDL_Rect *dstrectTab = (SDL_Rect*) calloc (nbRect,sizeof(SDL_Rect));;
    int **tabDir = (int**) calloc (nbRect,sizeof(int*));
    rectDirAlloc(dstrectTab,tabDir,nbRect);



    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        for(i=0;i<nbRect;i++)
        {
            if((dstrectTab[i].x <= 0) || (dstrectTab[i].x >= sWidth - bmp->w))
            {
                tabDir[i][0] *= (-1);
            }
            if((dstrectTab[i].y <= 0) || (dstrectTab[i].y >= sHeigth - bmp->h))
            {
                tabDir[i][1] *= (-1);
            }

            dstrectTab[i].x += tabDir[i][0]*50;
            dstrectTab[i].y += tabDir[i][1]*50;
        }




        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        //SDL_BlitSurface(bmp, 0, screen, &dstrect);
        drawMultipleRect(bmp,screen,dstrectTab,nbRect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    free(dstrectTab);
    free(tabDir);
    printf("Exited cleanly\n");
    return 0;
}
