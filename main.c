#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "functions.h"

#define OS 1 // 0 = Windows | 1 = Linux

#if OS == 0
   #include <windows.h>
#elif OS == 1
   #include <dlfcn.h>
#endif




//variable globale

SGameState gamestate;


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

    if(TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Surface *text1;
    //text1->w = 500;
    //text1->h = 30;
    TTF_Font *fontHacked = NULL;
    SDL_Rect fontPos;
    fontPos.x = 100;
    fontPos.y = 750;
    SDL_Color colorBlack = {255, 255, 255};


        /* Chargement de la police */
    fontHacked = TTF_OpenFont("hacked.ttf", 65);
    if(fontHacked == NULL)
    {
        printf("Erreur d'initialisation de Openfont : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    text1 = TTF_RenderText_Blended(fontHacked, "Backgammon Nantarena Edition", colorBlack);
    if(text1 == NULL)
    {
        printf("Erreur d'initialisation de RenderText : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    int sWidth=1241, sHeigth=811;
    // create a new window
    SDL_Window * window = SDL_CreateWindow(
        "Polygammon™",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        sWidth,                               // width, in pixels
        sHeigth,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *SDL_DisplayFormatAlpha(SDL_Surface *screen);
    if ( !screen )
    {
        printf("Unable to set 1241*811 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* backgroundBoard = IMG_Load("boardPolygammon.bmp");
    if (!backgroundBoard)
    {
        printf("Unable to load bitmap boardPolygammon.bmp: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectBoard;
    rectBoard.x = 0;
    rectBoard.y = 0;

    // load an image
    SDL_Surface* dameWsurf = IMG_Load("white_dame.bmp");
    if (!dameWsurf)
    {
        printf("Unable to load bitmap white_dame.bmp: %s\n", SDL_GetError());
        return 1;
    }



    SDL_Surface* dameBsurf = IMG_Load("black_dame.bmp");
    if (!dameWsurf)
    {
        printf("Unable to load bitmap black_dame.bmp: %s\n", SDL_GetError());
        return 1;
    }


    // centre the bitmap on screen


    srand(time(NULL));
    int i,j=0;
    Dame *damesTab = (Dame*) malloc (30*sizeof(Dame));
    initDamesTab(damesTab,30);

    // Initialisation des Hitboxes

    Hitbox *hitboxesTab = (Hitbox*) malloc (28*sizeof(Hitbox));
    //SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
    initHitBoxesTab(hitboxesTab,28,screen);


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
    int lastX=0,lastY=0;

    int cpt=0;
    while(!done)
    {



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
                    if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startMatch();
                        // appelle de j2startMatch();
                    }
                    printf("varou");
                    curState = SSTARTGAME;
                    break;

                case SSTARTGAME:
                    curPlayer = NOBODY;

                    initGameState(&gamestate);

                    setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
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
                            printf("jusque ici 1");
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
        while (SDL_PollEvent(&event))
        {
            // message processing loop


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
                            //printf("mouse position : %d %d\n",event.button.x,event.button.y);
                        }
                        if(event.key.keysym.sym == SDLK_n)
                        {
                            setScore(&gamestate); // on met à jour le score
                            if(curPlayer == BLACK)
                            {
                                curPlayer = WHITE;
                                printf("Player WHITE is playing (Score: %d)\n", gamestate.whiteScore);


                            }
                            else
                            {
                                curPlayer = BLACK;
                                printf("Player BLACK is playing (Score: %d)\n", gamestate.blackScore);
                            }
                        }





                        break;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    {
                        printf("mouse position2 : %d %d diffX : %d diffY : %d\n",event.button.x,event.button.y,event.button.x-lastX,event.button.y-lastY);
                        lastX =  event.button.x;
                        lastY =  event.button.y;
                        detectClickIntoHitbox(hitboxesTab,28,event.button.x,event.button.y);
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {


                            damesTab[j].rectDame->x = event.button.x;
                            damesTab[j].rectDame->y = event.button.y;
                        }

                        break;
                    }

                } // end switch


        }


            SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);

            SDL_BlitSurface(text1,0,screen, &fontPos);

            drawDames(damesTab,dameWsurf,dameBsurf,screen,30);



            SDL_UpdateWindowSurface(window);

            cpt++;
	   // printf("frame%d\n",cpt%100);
            SDL_Delay(15);



    } // end main loop

    // LIBERATION DE LA MEMOIRE
    SDL_FreeSurface(dameBsurf);
    SDL_FreeSurface(dameWsurf);

    TTF_CloseFont(fontHacked);
    TTF_Quit();

    SDL_FreeSurface(text1);
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // all is well ;)
    free(damesTab);
    printf("Exited cleanly\n");
    return 0;
}



