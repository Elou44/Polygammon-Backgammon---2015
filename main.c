#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>
#include "functions.h"

#define OS 1 // 0 = Windows | 1 = Linux

#if OS == 0
   #include <windows.h>
#elif OS == 1
   #include <dlfcn.h>
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

void drawDames(Dame *damesTab, SDL_Surface* screen, int nbDames)
{
    int i;
    //SDL_Rect dstrect;
    for(i = 0; i < nbDames ; i++)
    {
        //dstrect =  damesTab[i].rectDame;
        SDL_BlitSurface(damesTab[i].dameSurf,0,screen, damesTab[i].rectDame);
    }
}

void initDamesTab(Dame *damesTab, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf, int nbDames)
{
    int i;
    for(i = 0; i < nbDames; i++)
    {
        if(i<15)
        {
            damesTab[i].rectDame = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectDame
            damesTab[i].coulor=0;
            damesTab[i].dameSurf = dameWsurf;
            damesTab[i].rectDame->x = rand()%500;
            damesTab[i].rectDame->y = rand()%350;
        }
        else
        {
            damesTab[i].rectDame = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectDame
            damesTab[i].coulor=1;
            damesTab[i].dameSurf = dameBsurf;
            damesTab[i].rectDame->x = rand()%500;
            damesTab[i].rectDame->y = rand()%350;
        }

    }
}

void rollDices(unsigned char* dices)
{

    dices[0] =  rand()%6;
    dices[1] =  rand()%6;

}

int main ( int argc, char** argv )
{


    //************** CHARGEMENT DE L'API ***************//

    //char nomLib[50];
    //nomLib = "backgammonAPI.dll";

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

        if((InitLibrary=(pfInitLibrary)dlsym(lib,"InitLibrary"))==NULL)
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


    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    int sWidth=1310, sHeigth=900;
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(sWidth, sHeigth, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 1310x900 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* backgroundBoard = SDL_LoadBMP("boardPolygammon.bmp");
    if (!backgroundBoard)
    {
        printf("Unable to load bitmap boardPolygammon.bmp: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectBoard;
    rectBoard.x = 0;
    rectBoard.y = 0;

    // load an image
    SDL_Surface* dameWsurf = SDL_LoadBMP("white_dame.bmp");
    if (!dameWsurf)
    {
        printf("Unable to load bitmap white_dame.bmp: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetColorKey(dameWsurf, SDL_SRCCOLORKEY, SDL_MapRGB(dameWsurf->format, 255, 255, 255)); // on rend transparent le blanc de l'image

    SDL_Surface* dameBsurf = SDL_LoadBMP("black_dame.bmp");
    if (!dameWsurf)
    {
        printf("Unable to load bitmap black_dame.bmp: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetColorKey(dameBsurf, SDL_SRCCOLORKEY, SDL_MapRGB(dameBsurf->format, 255, 255, 255)); // on rend transparent le blanc de l'image

    // centre the bitmap on screen

    srand(time(NULL));
    int i,j=0;
    Dame *damesTab = (Dame*) malloc (30*sizeof(Dame));
    initDamesTab(damesTab,dameWsurf,dameBsurf,30);

    // Par convention, nous dirons que le joueur  BLACK est le j1 et le joueur WHITE est le j2

    States curState; // �tat courant du jeu
    GameMode gameMode; // mode de jeu
    curState = SINITLIBS;
    Player curPlayer; // joueur courant

    unsigned char j1Dices[2]; // dernier lanc� de d�s du j1
    unsigned char j2Dices[2]; // dernier lanc� de d�s du j2


    // program main loop
    bool done = false;
    SDL_Event event;
    while(!done)
    {
        while (SDL_PollEvent(&event))
        {
            // message processing loop
            
    
                switch(curState)
                {
    
                case SINITLIBS:
    
                    // appelle de initLib
                    //InitLibrary(nomLib); // pour test
    
                    if(argc ==2) // jeu IA vs Humain
                    {
                        gameMode = MHvsAI;
                        // appelle de j1InitLibrary(...);
                    }
                    else if(argc == 3) // jeu IA vs IA
                    {
                        // appelle de j1InitLibrary(...);
                        // appelle de j2InitLibrary(...);
    
                        gameMode = MAIvsAI;
                    }
                    else // humain vs humain
                    {
    
                        gameMode = MHvsH;
                    }
    
                    curState = SSTARTMATCH;
                    break;
    
                case SSTARTMATCH:
                    if(gameMode == MHvsAI)
                    {
                        // appelle de j1startMatch();
                    }
                    else if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startMatch();
                        // appelle de j2startMatch();
                    }
                    curState = SSTARTGAME;
                    break;
    
                case SSTARTGAME:
                    curPlayer = NOBODY;
                    if(gameMode == MHvsAI)
                    {
                        // appelle de j1startGame(BLACK);
                    }
                    else if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startGame(BLACK);
                        // appelle de j2startGame(WHITE);
                    }
    
                    curState = SROLLDICES;
                    break;
    
                case SROLLDICES:
                    if(curPlayer == NOBODY) // aucun joueur n'a �t� choisi pour commenc� la partie
                    {
                        int j1Sum = 0, j2Sum = 0;
                        rollDices(j1Dices);
                        rollDices(j2Dices);
    
                        j1Sum = (int) j1Dices[0]  + (int) j1Dices[1] ; // somme des d�s de j1
                        j2Sum = (int) j2Dices[0]  + (int) j2Dices[1] ; // somme des d�s de j2
    
                        if(j1Sum > j2Sum)
                        {
                            printf("j1Sum : %d | j2Sum : %d\n",j1Sum,j2Sum);
                            printf("Player BLACK begins\n");
                            curPlayer = BLACK;
                            curState = SPLAY;
                        }
                        else
                        {
                            printf("j1Sum : %d | j2Sum : %d\n",j1Sum,j2Sum);
                            printf("Player WHITE begins\n");
                            curPlayer = WHITE;
                            curState = SPLAY;
                        }
                    }
    
    
                    break;
    
                case SPLAY:
                    if(curPlayer == BLACK)
                    {
                        
                    } // end if
    
    
                    if(curPlayer == WHITE)
                    {
                        
                    } // end if
    
    
                        break;
    
                case SDOUBLETAKEN:
    
                    break;
    
                case SENDGAME:
    
                    break;
    
                case SENDMATCH:
    
                    break;
    
                }
    
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
                        {
                            done = true;
                        }
                        if (event.key.keysym.sym == SDLK_END)
                        {
                            j++;
                            if(j>29)
                            {
                                j=0;
                            }
                            printf("mouse position : %d %d\n",event.button.x,event.button.y);
                        }
                        if(event.key.keysym.sym == SDLK_n)
                        {
                            if(curPlayer == BLACK)
                            {
                                curPlayer = WHITE;
                                printf("Player WHITE is playing\n");
    
                            }
                            else
                            {
                                curPlayer = BLACK;
                                printf("Player BLACK is playing\n");
                            }
                        }
    
                        break;
                    }
                case SDL_MOUSEMOTION:
                    {
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            printf("mouse position2 : %d %d\n",event.button.x,event.button.y);
                            damesTab[j].rectDame->x = event.button.x;
                            damesTab[j].rectDame->y = event.button.y;
                        }
    
                        break;
                    }
    
                } // end switch
    
    
    
    
    
            // DRAWING STARTS HERE
    
            // clear screen
            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    
            // DESSINER L'ECRAN
    
            SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
            drawDames(damesTab,screen,30);
    
            // DRAWING ENDS HERE
    
            // finally, update the screen :)
            SDL_Flip(screen);
            SDL_Delay(16);
        }
    } // end main loop

    // LIBERATION DE LA MEMOIRE
    SDL_FreeSurface(dameBsurf);
    SDL_FreeSurface(dameWsurf);

    // all is well ;)
    free(damesTab);
    printf("Exited cleanly\n");
    return 0;
}
