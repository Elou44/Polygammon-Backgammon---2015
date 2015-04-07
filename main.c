#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <string.h>
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
        if((PlayTurn=(pfPlayTurn)dlsym(lib,"PlayTest"))==NULL)
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

    SDL_Surface *title;
    SDL_Rect fontPosTitle;
    fontPosTitle.x = 200;
    fontPosTitle.y = 780;

    SDL_Surface *textDices;
    SDL_Rect fontPosDices;
    fontPosDices.x = 430;
    fontPosDices.y = 720;

    SDL_Surface *textCurPlayer;
    SDL_Rect fontPosCurPlayer;
    fontPosCurPlayer.x = 1100;
    fontPosCurPlayer.y = 350;

    SDL_Surface *textScoreWhite;
    SDL_Rect fontPosScoreWhite;
    fontPosScoreWhite.x = 1100;
    fontPosScoreWhite.y = 50;


    SDL_Surface *textScoreBlack;
    SDL_Rect fontPosScoreBlack;
    fontPosScoreBlack.x = 1100;
    fontPosScoreBlack.y = 650;

    TTF_Font *fontHacked = NULL;


    SDL_Color colorFont = {145, 122, 205};
    SDL_Color colorFont1 = {255, 255, 255};
    SDL_Color colorFont2 = {50, 50, 50};


        /* Chargement de la police */
    fontHacked = TTF_OpenFont("Digital-Desolation.ttf", 15);
    if(fontHacked == NULL)
    {
        printf("Erreur d'initialisation de Openfont : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    title = TTF_RenderText_Blended(fontHacked, "Polygammon Nantarena Edition", colorFont);

    if(title == NULL)
    {
        printf("Erreur d'initialisation de RenderText : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    textDices = TTF_RenderText_Blended(fontHacked, "Dice1 | Dice2", colorFont);
    char strDices[10];

    textCurPlayer = TTF_RenderText_Blended(fontHacked, "NOBODY", colorFont);
    char strCurPlayer[15];

    textScoreWhite = TTF_RenderText_Blended(fontHacked, "WHITE : 167", colorFont);
    char strScoreWhite[15];

    textScoreBlack = TTF_RenderText_Blended(fontHacked, "BLACK : 167", colorFont);
    char strScoreBlack[15];

    //char machaine[6] = "WHITE";
    //textCurPlayer = TTF_RenderText_Blended(fontHacked, "lol", colorFont);
    //changeText(textCurPlayer,fontHacked,colorFont);



    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    int sWidth=1341, sHeigth=811;
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

    SDL_Surface* backgroundBoard = IMG_Load("boardPolygammonNA.png");
    if (!backgroundBoard)
    {
        printf("Unable to load bitmap boardPolygammon.bmp: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Rect rectBoard;
    rectBoard.x = 0;
    rectBoard.y = 0;

    // load an image
    SDL_Surface* dameWsurf = IMG_Load("white_dame2.png");
    if (!dameWsurf)
    {
        printf("Unable to load bitmap white_dame.bmp: %s\n", SDL_GetError());
        return 1;
    }



    SDL_Surface* dameBsurf = IMG_Load("black_dame2.png");
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
    
    
    SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
    // Initialisation des Hitboxes

    Hitbox *hitboxesTab = (Hitbox*) malloc (28*sizeof(Hitbox));
    //SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
    initHitBoxesTab(hitboxesTab,28,screen);


    // Par convention, nous dirons que le joueur  BLACK est le j1 et le joueur WHITE est le j2


    GameMode gameMode; // mode de jeu

    Player curPlayer; // joueur courant

    unsigned char dices[2]; // dernier lanc� de d�s du j1

    SMove moves[4];
    int indiceHBTab[2]; // indice des hitboxes cliquées pour 1 move


    unsigned int nbMoves = 0;


    // program main loop


    int lastX=0,lastY=0;

    int scoreToReach = 2; // score à atteindre pour gagner

    int j1GlobalScore = 0;
    int j2GlobalScore = 0;

  

    bool done = false;

    States curState; // �tat courant du jeu
    curState = SINITLIBS;

    SDL_Event event;

    int j1Tries = 0;

    int j2Tries = 0;

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

                        gameMode = MHvsAI;
                        char name[50] = "FreddyTGros";
                        InitLibrary(name);
                    }

                    curState = SSTARTMATCH;
                    break;

                case SSTARTMATCH:
                    if(gameMode == MHvsAI)
                    {
                        // appelle de j1startMatch();
                        StartMatch(1);

                    }
                    if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startMatch();
                        // appelle de j2startMatch();
                    }


                    curState = SSTARTGAME;
                    break;

                case SSTARTGAME:

                    curPlayer = NOBODY;

                    indiceHBTab[0] = -1; // initialisation du tableau d'indice des hitboxes cliquées
                    indiceHBTab[1] = -1;

                    j1Tries = 0;
                    j2Tries = 0;

                    //char *myStr = "hello%d", 1000;

                    initGameState(&gamestate);

                    setScore(&gamestate); // on met à jour le score

                    setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);

                    if(gameMode == MHvsAI)
                    {
                        // appelle de j1startGame(BLACK);
                        StartGame(BLACK);
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

                        rollDices(dices);
                        j1Sum = (int) dices[0]  + (int) dices[1] ; // somme des d�s de j1

                        rollDices(dices);
                        j2Sum = (int) dices[0]  + (int) dices[1] ; // somme des d�s de j2

                        if(j1Sum > j2Sum)
                        {
                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK BEGINS", colorFont2);
                            printf("j1Sum : %d | j2Sum : %d\n",j1Sum,j2Sum);
                            printf("Player BLACK begins\n");
                            curPlayer = BLACK;
                            curState = SPLAY;
                        }
                        else
                        {

                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE BEGINS", colorFont1);
                            printf("j1Sum : %d | j2Sum : %d\n",j1Sum,j2Sum);
                            printf("Player WHITE begins\n");
                            curPlayer = WHITE;
                            curState = SPLAY;
                        }

                    }


                    if(curPlayer == BLACK)
                    {
                        rollDices(dices);
                        sprintf(strDices, "%d | %d", dices[0],dices[1]);
                        textDices = TTF_RenderText_Blended(fontHacked,strDices, colorFont);
                        curState = SPLAY;

                    }

                    else if(curPlayer == WHITE)
                    {
                        rollDices(dices);
                        sprintf(strDices, "%d | %d", dices[0],dices[1]);
                        textDices = TTF_RenderText_Blended(fontHacked,strDices, colorFont);
                        curState = SPLAY;
                    }


                    break;

                case SPLAY:
                    if(gameMode == MHvsAI)
                    {
                        if(curPlayer == BLACK)
                        {
                            // appelle de playturn

                        } // end if


                        if(curPlayer == WHITE)
                        {

                        } // end if

                    }

                    break;

                case SDOUBLETAKEN:

                    break;

                case SENDGAME:
                    if(j1GlobalScore == scoreToReach || j2GlobalScore == scoreToReach)
                    {
                        curState = SENDMATCH;
                        SDL_Delay(1000);
                    }
                    else
                    {
                        curState = SSTARTGAME;
                        SDL_Delay(1000);
                    }


                    break;

                case SENDMATCH:

                    done = true;


                    break;

                }


        /* ***************************
         *                           *
         *   GESTION DES EVENEMENTS  *
         *                           *
         * **************************/


        if((curState == SPLAY) && (gameMode != MAIvsAI))
        {

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
                            if(event.key.keysym.sym == SDLK_n) // CHANGEMENT DE JOUEUR
                            {




                                //printf("indiceHBTab[0] = %d",indiceHBTab[0]);
                                //printf("indiceHBTab[1] = %d",indiceHBTab[1]);




                                indiceHBTab[0] = -1; // réinitialisation des Hitboxes cliquées
                                indiceHBTab[1] = -1;



                                if(curPlayer == BLACK)
                                {

                                    if(gameMode == MHvsAI)
                                    {
                                        PlayTurn(&gamestate, dices, moves, &nbMoves, j1Tries);
                                        //clickToSMoves(indiceHBTab,moves,&nbMoves,curPlayer);

                                        for(i = 0; i < nbMoves ; i++)
                                        {
                                            printf("moves (%d) IA added between %d and %d\n",nbMoves,moves[i].src_point,moves[i].dest_point);

                                        }

                                    }

                                    updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                    setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                    setScore(&gamestate); // on met à jour le score

                                    nbMoves = 0;

                                    printf("Player WHITE is playing (WHITE: %d)\n", gamestate.whiteScore);


                                    textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE TURN", colorFont1);

                                    sprintf(strScoreBlack, "BLACK : %d", gamestate.blackScore);
                                    textScoreBlack = TTF_RenderText_Blended(fontHacked,strScoreBlack, colorFont);

                                    if(gamestate.blackScore == 0)
                                    {
                                        curState = SENDGAME;
                                        j1GlobalScore++; // BLACK
                                        textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont2);
                                    }
                                    else
                                    {
                                        curState = SROLLDICES;
                                        curPlayer = WHITE;
                                    }

                                }

                                else
                                {
                                    printf("nbMoves WHITE : %d\n",nbMoves);
                                    updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                    setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                    setScore(&gamestate); // on met à jour le score

                                    nbMoves = 0;

                                    printf("Player BLACK is playing (BLACK:%d)\n", gamestate.blackScore);

                                    textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK TURN", colorFont2);



                                    sprintf(strScoreWhite, "WHITE : %d", gamestate.whiteScore);
                                    textScoreWhite = TTF_RenderText_Blended(fontHacked,strScoreWhite, colorFont);

                                    if(gamestate.whiteScore == 0 )
                                    {
                                        curState = SENDGAME;
                                        j2GlobalScore++; // WHITE
                                        textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                                    }
                                    else
                                    {
                                        curState = SROLLDICES;
                                        curPlayer = BLACK;
                                    }
                                }
                            }

                            if(event.key.keysym.sym == SDLK_r) // Réinitialiser les mouvements
                            {
                                nbMoves = 0;
                                indiceHBTab[0] = -1; // réinitialisation des Hitboxes cliquées
                                indiceHBTab[1] = -1;
                            }





                            break;
                        }
                    case SDL_MOUSEBUTTONDOWN:
                        {
                            //printf("mouse position2 : %d %d diffX : %d diffY : %d\n",event.button.x,event.button.y,event.button.x-lastX,event.button.y-lastY);
                            lastX =  event.button.x;
                            lastY =  event.button.y;
                            //detectClickIntoHitbox(hitboxesTab,28,event.button.x,event.button.y);

                            if(gameMode == MHvsH || (gameMode == MHvsAI && curPlayer == WHITE))
                            {
                                if(detectClickIntoHitbox(hitboxesTab,28,event.button.x,event.button.y) != -1) // on vérifie qu'on clique bien sur une hitbox
                                {
                                    if(indiceHBTab[0] == -1) indiceHBTab[0] = detectClickIntoHitbox(hitboxesTab,28,event.button.x,event.button.y); // mouvement non terminé
                                    else if(indiceHBTab[1] == -1)
                                    {
                                        indiceHBTab[1] = detectClickIntoHitbox(hitboxesTab,28,event.button.x,event.button.y);
                                        clickToSMoves(indiceHBTab,moves,&nbMoves,curPlayer);
                                    }
                                }

                            }


                            break;
                        }

                    } // end switch


                    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

                    SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);

                    SDL_BlitSurface(title,0,screen, &fontPosTitle);
                    SDL_BlitSurface(textDices,0,screen, &fontPosDices);
                    SDL_BlitSurface(textCurPlayer,0,screen, &fontPosCurPlayer);
                    SDL_BlitSurface(textScoreWhite,0,screen, &fontPosScoreWhite);
                    SDL_BlitSurface(textScoreBlack,0,screen, &fontPosScoreBlack);

                    //printf("%d\n", gamestate.board[23].nbDames);
                    drawDames(damesTab,dameWsurf,dameBsurf,screen,30);



                    SDL_UpdateWindowSurface(window);


                    SDL_Delay(15);


            }

        }






    } // end main loop

    // LIBERATION DE LA MEMOIRE
    SDL_FreeSurface(dameBsurf);
    SDL_FreeSurface(dameWsurf);

    TTF_CloseFont(fontHacked);
    TTF_Quit();

    SDL_FreeSurface(title);
    SDL_FreeSurface(textDices);
    SDL_FreeSurface(textCurPlayer);
    SDL_FreeSurface(textScoreWhite);
    SDL_FreeSurface(textScoreBlack);

    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // all is well ;)
    free(damesTab);
    printf("Exited cleanly\n");
    return 0;
}



