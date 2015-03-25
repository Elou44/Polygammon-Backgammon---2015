#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>
#include "functions.h"

#define OS 0 // 0 = Windows | 1 = Linux

#if OS == 0
   #include <windows.h>
#elif OS == 1
   #include <dlfnc.h>
#endif

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

    //************** CHARGEMENT DE L'API ***************//

    #if OS == 0

    // ON WINDOWS
        HINSTANCE hGetProcIDDLL = LoadLibrary("backgammonAPI.dll");

        if (!hGetProcIDDLL) {
            printf("could not load the lib");
            return EXIT_FAILURE;
        }

        // resolve function address here

        pfInitLibrary InitLibrary = (pfInitLibrary)GetProcAddress(hGetProcIDDLL, "InitLibrary");
        if (!InitLibrary) {
            printf("could not locate the function InitLibrary");
            return EXIT_FAILURE;
        }
        pfStartMatch StartMatch = (pfStartMatch)GetProcAddress(hGetProcIDDLL, "StartMatch");
        if (!StartMatch) {
            printf("could not locate the function StartMatch");
            return EXIT_FAILURE;
        }
        pfStartGame StartGame = (pfStartGame)GetProcAddress(hGetProcIDDLL, "StartGame");
        if (!StartGame) {
            printf("could not locate the function StartGame");
            return EXIT_FAILURE;
        }
        pfEndGame EndGame = (pfEndGame)GetProcAddress(hGetProcIDDLL, "EndGame");
        if (!EndGame) {
            printf("could not locate the function EndGame");
            return EXIT_FAILURE;
        }
        pfEndMatch EndMatch = (pfEndMatch)GetProcAddress(hGetProcIDDLL, "EndMatch");
        if (!EndMatch) {
            printf("could not locate the function EndMatch");
            return EXIT_FAILURE;
        }
        pfDoubleStack DoubleStack = (pfDoubleStack)GetProcAddress(hGetProcIDDLL, "DoubleStack");
        if (!DoubleStack) {
            printf("could not locate the function DoubleStack");
            return EXIT_FAILURE;
        }
        pfTakeDouble TakeDouble = (pfTakeDouble)GetProcAddress(hGetProcIDDLL, "TakeDouble");
        if (!TakeDouble) {
            printf("could not locate the function TakeDouble");
            return EXIT_FAILURE;
        }
        pfPlayTurn PlayTurn = (pfPlayTurn)GetProcAddress(hGetProcIDDLL, "PlayTurn");
        if (!PlayTurn) {
            printf("could not locate the function PlayTurn");
            return EXIT_FAILURE;
        }

    #elif OS == 1

    // ON LINUX

        void * lib;

        pfInitLibrary InitLibrary;
        pfStartMatch StartMatch;
        pfStartGame StartGame;
        pfEndGame EndGame;
        pfEndMatch EndMatch;
        pfDoubleStack DoubleStack;
        pfTakeDouble TakeDouble;
        pfPlayTurn PlayTurn;

        if((lib=dlopen("backgammonAPI.so", RTLD_LAZY))==NULL)
        {
            // Erreur de chargement de la librairie
            printf("error chargement lib");
            return(false);
        }

        if((InitLibrary=(pfInitLibrary)dlsym(lib,"InitLabrary"))==NULL)
        {
            printf("could not locate the function InitLibrary");
            return EXIT_FAILURE;
        }
        if((StartMatch=(pfStartMatch)dlsym(lib,"StartMatch"))==NULL)
        {
            printf("could not locate the function StartMatch");
            return EXIT_FAILURE;
        }
        if((StartGame=(pfStartGame)dlsym(lib,"StartGame"))==NULL)
        {
            printf("could not locate the function StartGame");
            return EXIT_FAILURE;
        }
        if((EndGame=(pfEndGame)dlsym(lib,"EndGame"))==NULL)
        {
            printf("could not locate the function EndGame");
            return EXIT_FAILURE;
        }
        if((EndMatch=(pfEndMatch)dlsym(lib,"EndMatch"))==NULL)
        {
            printf("could not locate the function EndMatch");
            return EXIT_FAILURE;
        }
        if((DoubleStack=(pfDoubleStack)dlsym(lib,"DoubleStack"))==NULL)
        {
            printf("could not locate the function DoubleStack");
            return EXIT_FAILURE;
        }
        if((TakeDouble=(pfTakeDouble)dlsym(lib,"TakeDouble"))==NULL)
        {
            printf("could not locate the function TakeDouble");
            return EXIT_FAILURE;
        }
        if((PlayTurn=(pfPlayTurn)dlsym(lib,"PlayTurn"))==NULL)
        {
            printf("could not locate the function PlayTurn");
            return EXIT_FAILURE;
        }

    #endif // if

    EndGame();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    int sWidth=640, sHeigth=640;
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
        SDL_Delay(30);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    free(dstrectTab);
    free(tabDir);
    printf("Exited cleanly\n");
    return 0;
}
