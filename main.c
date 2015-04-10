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

#ifdef _WIN32
	#define OS 0 // 0 = Windows | 1 = Linux
#elif _WIN64
	#define OS 0

#elif __linux
	#define OS 1
#endif

#if OS == 0
   #include <windows.h>
#elif OS == 1
   #include <dlfcn.h>
#endif




//variable globale
unsigned int t = 0;



int main ( int argc, char** argv )
{


    SGameState gamestate;

    GameMode gameMode;

    unsigned int scoreToReach = 1; // score à atteindre pour gagner
    char *j1NomLib = (char*) malloc (50*sizeof(char));
    char *j2NomLib = (char*) malloc (50*sizeof(char));
    unsigned int delay = 500; // delay après affichage


    switch(argc) // Lecture des arguments de la commande de lancement
    {
    case 2:

        gameMode = MHvsH;
        scoreToReach = *argv[1] - (int) '0';

	break;

    case 3:

        gameMode = MHvsAI;
        j1NomLib = argv[1];
        scoreToReach = *argv[2] - (int) '0';
        printf("scoreToReach %d\n",scoreToReach);

        break;

    case 4:

        gameMode = MAIvsAI;
        j1NomLib = argv[1];
        j2NomLib = argv[2];

        

        scoreToReach = *argv[3] - (int) '0';

        break;

    default:

        gameMode = MHvsH;
        scoreToReach = 1;

        break;

    }


    /* ***************************
     *                           *
     *   CHARGEMENTS DES LIBS    *
     *                           *
     * **************************/

    #if OS == 0

    pfInitLibrary j1InitLibrary;
    pfStartMatch j1StartMatch;
    pfStartGame j1StartGame;
    pfEndGame j1EndGame;
    pfEndMatch j1EndMatch;
    pfDoubleStack j1DoubleStack;
    pfTakeDouble j1TakeDouble;
    pfPlayTurn j1PlayTurn;


	if(gameMode == MHvsAI)
	{
	    // ON WINDOWS
	    HINSTANCE hGetProcIDDLL = LoadLibrary(j1NomLib);

	    if (!hGetProcIDDLL) {
		printf("could not load the lib");
		return EXIT_FAILURE;
	    }

	    // resolve function address here

	    j1InitLibrary = (pfInitLibrary)GetProcAddress(hGetProcIDDLL, "InitLibrary");
	    if (!j1InitLibrary) {
		printf("could not locate the function InitLibrary");
		return EXIT_FAILURE;
	    }
	    j1StartMatch = (pfStartMatch)GetProcAddress(hGetProcIDDLL, "StartMatch");
	    if (!j1StartMatch) {
		printf("could not locate the function StartMatch");
		return EXIT_FAILURE;
	    }
	    j1StartGame = (pfStartGame)GetProcAddress(hGetProcIDDLL, "StartGame");
	    if (!j1StartGame) {
		printf("could not locate the function StartGame");
		return EXIT_FAILURE;
	    }
	    j1EndGame = (pfEndGame)GetProcAddress(hGetProcIDDLL, "EndGame");
	    if (!j1EndGame) {
		printf("could not locate the function EndGame");
		return EXIT_FAILURE;
	    }
	    j1EndMatch = (pfEndMatch)GetProcAddress(hGetProcIDDLL, "EndMatch");
	    if (!j1EndMatch) {
		printf("could not locate the function EndMatch");
		return EXIT_FAILURE;
	    }
	    j1DoubleStack = (pfDoubleStack)GetProcAddress(hGetProcIDDLL, "DoubleStack");
	    if (!j1DoubleStack) {
		printf("could not locate the function DoubleStack");
		return EXIT_FAILURE;
	    }
	    j1TakeDouble = (pfTakeDouble)GetProcAddress(hGetProcIDDLL, "TakeDouble");
	    if (!j1TakeDouble) {
		printf("could not locate the function TakeDouble");
		return EXIT_FAILURE;
	    }
	    j1PlayTurn = (pfPlayTurn)GetProcAddress(hGetProcIDDLL, "PlayTurn");
	    if (!j1PlayTurn) {
		printf("could not locate the function PlayTurn");
		return EXIT_FAILURE;
	    }

	}

	pfInitLibrary j2InitLibrary;
	pfStartMatch j2StartMatch;
	pfStartGame j2StartGame;
	pfEndGame j2EndGame;
	pfEndMatch j2EndMatch;
	pfDoubleStack j2DoubleStack;
	pfTakeDouble j2TakeDouble;
	pfPlayTurn j2PlayTurn;




	if(gameMode == MAIvsAI)
	{
	    // ON WINDOWS IA2
	    HINSTANCE hGetProcIDDLL2 = LoadLibrary(j2NomLib);

	    if (!hGetProcIDDLL2) {
		printf("could not load the lib");
		return EXIT_FAILURE;
	    }

	    // resolve function address here

	    j2InitLibrary = (pfInitLibrary)GetProcAddress(hGetProcIDDLL2, "InitLibrary");
	    if (!j2InitLibrary) {
		printf("could not locate the function InitLibrary");
		return EXIT_FAILURE;
	    }
	    j2StartMatch = (pfStartMatch)GetProcAddress(hGetProcIDDLL2, "StartMatch");
	    if (!j2StartMatch) {
		printf("could not locate the function StartMatch");
		return EXIT_FAILURE;
	    }
	    j2StartGame = (pfStartGame)GetProcAddress(hGetProcIDDLL2, "StartGame");
	    if (!j2StartGame) {
		printf("could not locate the function StartGame");
		return EXIT_FAILURE;
	    }
	    j2EndGame = (pfEndGame)GetProcAddress(hGetProcIDDLL2, "EndGame");
	    if (!j2EndGame) {
		printf("could not locate the function EndGame");
		return EXIT_FAILURE;
	    }
	    j2EndMatch = (pfEndMatch)GetProcAddress(hGetProcIDDLL2, "EndMatch");
	    if (!j2EndMatch) {
		printf("could not locate the function EndMatch");
		return EXIT_FAILURE;
	    }
	    j2DoubleStack = (pfDoubleStack)GetProcAddress(hGetProcIDDLL2, "DoubleStack");
	    if (!j2DoubleStack) {
		printf("could not locate the function DoubleStack");
		return EXIT_FAILURE;
	    }
	    j2TakeDouble = (pfTakeDouble)GetProcAddress(hGetProcIDDLL2, "TakeDouble");
	    if (!j2TakeDouble) {
		printf("could not locate the function TakeDouble");
		return EXIT_FAILURE;
	    }
	    j2PlayTurn = (pfPlayTurn)GetProcAddress(hGetProcIDDLL2, "PlayTurn");
	    if (!j2PlayTurn) {
		printf("could not locate the function PlayTurn");
		return EXIT_FAILURE;
	    }

	}


    #elif OS == 1 // ON LINUX IA1 (CHARGEMENT LIBRAIRIE)

    void * lib;

    pfInitLibrary j1InitLibrary;
    pfStartMatch j1StartMatch;
    pfStartGame j1StartGame;
    pfEndGame j1EndGame;
    pfEndMatch j1EndMatch;
    pfDoubleStack j1DoubleStack;
    pfTakeDouble j1TakeDouble;
    pfPlayTurn j1PlayTurn;

	if(gameMode == MHvsAI || gameMode == MAIvsAI)
	{

	    if((lib=dlopen(j1NomLib, RTLD_LAZY))==NULL)
	    {
		// Erreur de chargement de la librairie
		printf("error chargement lib");
		return(false);
	    }

	    if((j1InitLibrary=(pfInitLibrary)dlsym(lib,"InitLibrary"))==NULL)
	    {
		printf("could not locate the function InitLibrary");
		return EXIT_FAILURE;
	    }
	    if((j1StartMatch=(pfStartMatch)dlsym(lib,"StartMatch"))==NULL)
	    {
		printf("could not locate the function StartMatch");
		return EXIT_FAILURE;
	    }
	    if((j1StartGame=(pfStartGame)dlsym(lib,"StartGame"))==NULL)
	    {
		printf("could not locate the function StartGame");
		return EXIT_FAILURE;
	    }
	    if((j1EndGame=(pfEndGame)dlsym(lib,"EndGame"))==NULL)
	    {
		printf("could not locate the function EndGame");
		return EXIT_FAILURE;
	    }
	    if((j1EndMatch=(pfEndMatch)dlsym(lib,"EndMatch"))==NULL)
	    {
		printf("could not locate the function EndMatch");
		return EXIT_FAILURE;
	    }
	    if((j1DoubleStack=(pfDoubleStack)dlsym(lib,"DoubleStack"))==NULL)
	    {
		printf("could not locate the function DoubleStack");
		return EXIT_FAILURE;
	    }
	    if((j1TakeDouble=(pfTakeDouble)dlsym(lib,"TakeDouble"))==NULL)
	    {
		printf("could not locate the function TakeDouble");
		return EXIT_FAILURE;
	    }
	    if((j1PlayTurn=(pfPlayTurn)dlsym(lib,"PlayTest"))==NULL)
	    {
		printf("could not locate the function PlayTurn");
		return EXIT_FAILURE;
	    }

	}

    void * lib2;

    pfInitLibrary j2InitLibrary;
    pfStartMatch j2StartMatch;
    pfStartGame j2StartGame;
    pfEndGame j2EndGame;
    pfEndMatch j2EndMatch;
    pfDoubleStack j2DoubleStack;
    pfTakeDouble j2TakeDouble;
    pfPlayTurn j2PlayTurn;


	if(gameMode == MAIvsAI) // ON LINUX IA2 (CHARGEMENT LIBRAIRIE)
	{


	    if((lib2=dlopen(j2NomLib, RTLD_LAZY))==NULL)
	    {
		// Erreur de chargement de la librairie
		printf("error chargement lib2");
		return(false);
	    }

	    if((j2InitLibrary=(pfInitLibrary)dlsym(lib2,"InitLibrary"))==NULL)
	    {
		printf("could not locate the function InitLibrary");
		return EXIT_FAILURE;
	    }
	    if((j2StartMatch=(pfStartMatch)dlsym(lib2,"StartMatch"))==NULL)
	    {
		printf("could not locate the function StartMatch");
		return EXIT_FAILURE;
	    }
	    if((j2StartGame=(pfStartGame)dlsym(lib2,"StartGame"))==NULL)
	    {
		printf("could not locate the function StartGame");
		return EXIT_FAILURE;
	    }
	    if((j2EndGame=(pfEndGame)dlsym(lib2,"EndGame"))==NULL)
	    {
		printf("could not locate the function EndGame");
		return EXIT_FAILURE;
	    }
	    if((j2EndMatch=(pfEndMatch)dlsym(lib2,"EndMatch"))==NULL)
	    {
		printf("could not locate the function EndMatch");
		return EXIT_FAILURE;
	    }
	    if((j2DoubleStack=(pfDoubleStack)dlsym(lib2,"DoubleStack"))==NULL)
	    {
		printf("could not locate the function DoubleStack");
		return EXIT_FAILURE;
	    }
	    if((j2TakeDouble=(pfTakeDouble)dlsym(lib2,"TakeDouble"))==NULL)
	    {
		printf("could not locate the function TakeDouble");
		return EXIT_FAILURE;
	    }
	    if((j2PlayTurn=(pfPlayTurn)dlsym(lib2,"PlayTest"))==NULL)
	    {
		printf("could not locate the function PlayTurn");
		return EXIT_FAILURE;
	    }

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



    /* ***************************
     *                           *
     *   PLACEMENT DES TEXTES    *
     *                           *
     * **************************/

    SDL_Surface *title;
    SDL_Rect fontPosTitle;
    fontPosTitle.x = 280;
    fontPosTitle.y = 780;

    SDL_Surface *textDices;
    SDL_Rect fontPosDices;
    fontPosDices.x = 490;
    fontPosDices.y = 720;

    SDL_Surface *textCurPlayer;
    SDL_Rect fontPosCurPlayer;
    fontPosCurPlayer.x = 1125;
    fontPosCurPlayer.y = 332;

    SDL_Surface *textScoreWhite;
    SDL_Rect fontPosScoreWhite;
    fontPosScoreWhite.x = 1150;
    fontPosScoreWhite.y = 50;


    SDL_Surface *textScoreBlack;
    SDL_Rect fontPosScoreBlack;
    fontPosScoreBlack.x = 1150;
    fontPosScoreBlack.y = 613;

    TTF_Font *fontHacked = NULL;
    
    
    
    
    SDL_Color colorFont = {145, 122, 205}; // Définition des couleurs
    SDL_Color colorFont1 = {255, 255, 255};
    SDL_Color colorFont2 = {0, 0, 0};


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


    textScoreWhite = TTF_RenderText_Blended(fontHacked, "WHITE : 167", colorFont1);
    char strScoreWhite[15];

    textScoreBlack = TTF_RenderText_Blended(fontHacked, "BLACK : 167", colorFont2);
    char strScoreBlack[15];


    /* ***************************
     *                           *
     *   DECLARATION DES BOUTONS *
     *                           *
     * **************************/


    
    Button *bRollDices = (Button*) malloc (sizeof(Button));
    bRollDices->state = 0;
    bRollDices->rectButton.x = 234;
    bRollDices->rectButton.y = 706;
    bRollDices->rectButton.w = 230;
    bRollDices->rectButton.h = 48;

    bRollDices->rectText.x = 234;
    bRollDices->rectText.y = 706;

    SDL_Surface *bRTextSurf = TTF_RenderText_Blended(fontHacked, "Roll Dices", colorFont2);

    
    Button *bAccept = (Button*) malloc (sizeof(Button));
    bAccept->state = 0;
    bAccept->rectButton.x = 1053;
    bAccept->rectButton.y = 317;
    bAccept->rectButton.w = 50;
    bAccept->rectButton.h = 50;

    bAccept->rectText.x = 1053;
    bAccept->rectText.y = 317;  

    SDL_Surface *bATextSurf = TTF_RenderText_Blended(fontHacked, "OK", colorFont2);

    
    Button *bDoubleStack = (Button*) malloc (sizeof(Button));
    bDoubleStack->state = 0;
    bDoubleStack->rectButton.x = 576;
    bDoubleStack->rectButton.y = 706;
    bDoubleStack->rectButton.w = 230;
    bDoubleStack->rectButton.h = 48;

    bDoubleStack->rectText.x = 576;
    bDoubleStack->rectText.y = 706;  

    SDL_Surface *bDTextSurf = TTF_RenderText_Blended(fontHacked, "Double Stack", colorFont2);

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


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


    SDL_SetWindowIcon(window, dameBsurf);

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




    Player curPlayer; // joueur courant

    unsigned char dices[2]; // dernier lanc� de d�s du j1

    SMove moves[4];
    int indiceHBTab[2]; // indice des hitboxes cliquées pour 1 move

    unsigned int nbMoves = 0;

    int lastX=0,lastY=0;

    int j1GlobalScore = 0;
    int j2GlobalScore = 0;

    bool done = false;

    States curState; // �tat courant du jeu
    curState = SINITLIBS;

    SDL_Event event;

    int j1Tries = 0;

    int j2Tries = 0;

    char j1Name[50];
    char j2Name[50];


    while(!done)
    {

                switch(curState)
                {

                case SINITLIBS:


                    // appelle de initLib
                    //InitLibrary(nomLib); // pour test
                    if(gameMode==MHvsH) // jeu IA vs Humain
                    {


                    }
                    else if(gameMode==MHvsAI)
        		    {
        		         // appelle de j1InitLibrary(...);
                        j1InitLibrary(j1Name);
        		    }
                    else if(gameMode==MAIvsAI) // jeu IA vs IA
                    {

                        // appelle de j1InitLibrary(...);
                        j1InitLibrary(j1Name);
                        // appelle de j2InitLibrary(...);
                        j2InitLibrary(j2Name);

                    }

                    curState = SSTARTMATCH;

                    break;

                case SSTARTMATCH:

                    if(gameMode == MHvsAI)
                    {
                        // appelle de j1startMatch();
                        j1StartMatch(scoreToReach);

                    }
                    else if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startMatch();
			             j1StartMatch(scoreToReach);
                         printf("j2NomLib!! %s\n",j2NomLib);

                        // appelle de j2startMatch();
			             j2StartMatch(scoreToReach);
                         

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
                        j1StartGame(BLACK);
                    }
                    else if(gameMode == MAIvsAI)
                    {
                        // appelle de j1startGame(BLACK);
                        j1StartGame(BLACK);
                        // appelle de j2startGame(WHITE);
			            j2StartGame(WHITE);
                    }

                    curState = SDOUBLESTACK;
                    break;

                case SDOUBLESTACK:

                    if(gameMode == MAIvsAI || (curPlayer == BLACK && gameMode == MHvsAI))
                    {
                        curState = SROLLDICES;
                        bRollDices->state = 0;
                        bDoubleStack->state = 0;
                        printf("here11111\n");
                    }
                    else
                    {
                        bRollDices->state = 1;
                        bDoubleStack->state = 1;
                        bAccept->state = 0;
                    }




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
                            curState = SDOUBLESTACK;
    
                        }
                        else
                        {

                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE BEGINS", colorFont1);
                            printf("j1Sum : %d | j2Sum : %d\n",j1Sum,j2Sum);
                            printf("Player WHITE begins\n");
                            curPlayer = WHITE;
                            curState = SDOUBLESTACK;

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

                    bAccept->state = 1;
   
                    if(gameMode == MAIvsAI || gameMode == MHvsAI)
                    {
                        if(curPlayer == BLACK)
                        {
                            // appelle de j1Playturn
			                 j1PlayTurn(&gamestate, dices, moves, &nbMoves, j1Tries);


                            if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                            {

                                updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                setScore(&gamestate); // on met à jour le score

                            }
                            else
                            {
                                //j1Tries++; // on incrémente le compteur de pénalité du joueur courant 
                            }

                            nbMoves = 0;

                            printf("Player WHITE is playing (WHITE: %d)\n", gamestate.whiteScore);


                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE TURN", colorFont1);

                            sprintf(strScoreBlack, "BLACK : %d", gamestate.blackScore);
                            textScoreBlack = TTF_RenderText_Blended(fontHacked,strScoreBlack, colorFont2);

                            SDL_Delay(delay); // Delay en ms

                            if(gamestate.blackScore == 0)
                            {
                                curState = SENDGAME;
                                j1GlobalScore += gamestate.stake; // BLACK
                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont2);
                            }
                            else if(j1Tries > 3)
                            {
                                curState = SENDGAME;
                                j2GlobalScore += gamestate.stake; // WHITE
                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                            }
                            else
                            {
                                curState = SDOUBLESTACK;
                                curPlayer = WHITE;
                            }




                        } // end if


                        if(curPlayer == WHITE && gameMode == MAIvsAI)
                        {

			                 // appelle de j1Playturn
			                 j2PlayTurn(&gamestate, dices, moves, &nbMoves, j1Tries);

                            printf("nbMoves WHITE : %d\n",nbMoves);


                            if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                            {

                                updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                setScore(&gamestate); // on met à jour le score

                            }
                            else
                            {
                                //j2Tries++; // on incrémente le compteur de pénalité du joueur courant 
                            }

                            nbMoves = 0;

                            printf("Player BLACK is playing (BLACK:%d)\n", gamestate.blackScore);

                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK TURN", colorFont2);



                            sprintf(strScoreWhite, "WHITE : %d", gamestate.whiteScore);
                            textScoreWhite = TTF_RenderText_Blended(fontHacked,strScoreWhite, colorFont1);

                            SDL_Delay(delay); // Delay en ms

                            if(gamestate.whiteScore == 0 )
                            {
                                curState = SENDGAME;
                                j2GlobalScore += gamestate.stake; // WHITE
                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                            }
                            else if(j2Tries > 3)
                            {
                                curState = SENDGAME;
                                j1GlobalScore += gamestate.stake; // BLACK
                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont1);
                            }
                            else
                            {
                                curState = SDOUBLESTACK;
                                curPlayer = BLACK;
                            }


                        } // end if

                    }


                    break;

                case SDOUBLETAKEN:

                    // call tDoubleTaken

                    break;

                case SENDGAME:

                    if(j1GlobalScore >= scoreToReach || j2GlobalScore >= scoreToReach)
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


        /*if(curState == SPLAY)
        {*/

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


                            if(event.key.keysym.sym == SDLK_n) // CHANGEMENT DE JOUEUR
                            {

                                /*if(gameMode != MAIvsAI) // si on est dans un mode de jeu autre que IAvsIA alors on accepte l'appui sur la touche N (changement de joueur)
                                {


                                    indiceHBTab[0] = -1; // réinitialisation des Hitboxes cliquées
                                    indiceHBTab[1] = -1;


                                    if(curPlayer == WHITE && (gameMode == MHvsAI || gameMode == MHvsH))
                                    {
                                        printf("nbMoves WHITE : %d\n",nbMoves);

                                        if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                                        {

                                            updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                            setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                            setScore(&gamestate); // on met à jour le score

                                        }
                                        else
                                        {
                                            //j2Tries++; // on incrémente le compteur de pénalité du joueur courant 
                                        }

                                        nbMoves = 0;

                                        printf("Player BLACK is playing (BLACK:%d)\n", gamestate.blackScore);

                                        textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK TURN", colorFont2);

                                        sprintf(strScoreWhite, "WHITE : %d", gamestate.whiteScore);

                                        textScoreWhite = TTF_RenderText_Blended(fontHacked,strScoreWhite, colorFont1);


                                        if(gamestate.whiteScore == 0 )
                                        {
                                            curState = SENDGAME;
                                            j2GlobalScore += gamestate.stake; // WHITE
                                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                                        }
                                        else if(j2Tries > 3)
                                        {
                                            curState = SENDGAME;
                                            j1GlobalScore += gamestate.stake; // BLACK
                                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont1);
                                        }
                                        else
                                        {
                                            curState = SROLLDICES;
                                            curPlayer = BLACK;
                                        }
                                    }
                                    
                                    else if(curPlayer == BLACK && gameMode == MHvsH)
                				    {
                				      
                                        if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                                        {

                                            updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                            setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                            setScore(&gamestate); // on met à jour le score

                                        }
                                        else
                                        {
                                            j1Tries++; // on incrémente le compteur de pénalité du joueur courant 
                                        }

                    					nbMoves = 0;

                    					printf("Player WHITE is playing (WHITE: %d)\n", gamestate.whiteScore);


                    					textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE TURN", colorFont1);

                    					sprintf(strScoreBlack, "BLACK : %d", gamestate.blackScore);
                    					textScoreBlack = TTF_RenderText_Blended(fontHacked,strScoreBlack, colorFont2);

                    					if(gamestate.blackScore == 0)
                    					{
                    					    curState = SENDGAME;
                    					    j1GlobalScore += gamestate.stake; // BLACK
                    					    textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont2);
                    					}
                                        else if(j1Tries > 3)
                                        {
                                            curState = SENDGAME;
                                            j2GlobalScore += gamestate.stake; // WHITE
                                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                                        }
                    					else
                    					{
                    					    curState = SROLLDICES;
                    					    curPlayer = WHITE;
                    					}
                				      
                				    }
                                }*/
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
                            // détection de clic sur le bouton OK
                            if(((event.button.x >= bAccept->rectButton.x) && (event.button.x <= bAccept->rectButton.x + bAccept->rectButton.w)) && ((event.button.y >= bAccept->rectButton.y) && (event.button.y <= bAccept->rectButton.y + bAccept->rectButton.h)))
                            {
                                if(bAccept->state == 1) // Si le bouton OK est activé
                                {

                                    if(gameMode != MAIvsAI) // si on est dans un mode de jeu autre que IAvsIA alors on accepte l'appui sur la touche N (changement de joueur)
                                    {


                                        indiceHBTab[0] = -1; // réinitialisation des Hitboxes cliquées
                                        indiceHBTab[1] = -1;


                                        if(curPlayer == WHITE && (gameMode == MHvsAI || gameMode == MHvsH))
                                        {
                                            printf("nbMoves WHITE : %d\n",nbMoves);

                                            if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                                            {

                                                updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                                setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                                setScore(&gamestate); // on met à jour le score

                                            }
                                            else
                                            {
                                                //j2Tries++; // on incrémente le compteur de pénalité du joueur courant 
                                            }

                                            nbMoves = 0;

                                            printf("Player BLACK is playing (BLACK:%d)\n", gamestate.blackScore);

                                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK TURN", colorFont2);

                                            sprintf(strScoreWhite, "WHITE : %d", gamestate.whiteScore);

                                            textScoreWhite = TTF_RenderText_Blended(fontHacked,strScoreWhite, colorFont1);


                                            if(gamestate.whiteScore == 0 )
                                            {
                                                bAccept->state = 0;
                                                curState = SENDGAME;
                                                j2GlobalScore += gamestate.stake; // WHITE
                                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                                            }
                                            else if(j2Tries > 3)
                                            {
                                                bAccept->state = 0;
                                                curState = SENDGAME;
                                                j1GlobalScore += gamestate.stake; // BLACK
                                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont1);
                                            }
                                            else
                                            {
                                                bAccept->state = 0;
                                                bRollDices->state = 1;
                                                bDoubleStack->state = 1;
                                                curState = SDOUBLESTACK;
                                                curPlayer = BLACK;
                                            }
                                        }
                                        
                                        else if(curPlayer == BLACK && gameMode == MHvsH)
                                        {
                                          
                                            if(arbitre(&gamestate, curPlayer, nbMoves, moves, dices) == 0) // Si l'arbitre accepte les mouvements
                                            {

                                                updateSGameState(&gamestate,moves,&nbMoves,curPlayer);
                                                setDamesPos(damesTab,&gamestate, dameWsurf, dameBsurf);
                                                setScore(&gamestate); // on met à jour le score

                                            }
                                            else
                                            {
                                                j1Tries++; // on incrémente le compteur de pénalité du joueur courant 
                                            }

                                            nbMoves = 0;

                                            printf("Player WHITE is playing (WHITE: %d)\n", gamestate.whiteScore);


                                            textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE TURN", colorFont1);

                                            sprintf(strScoreBlack, "BLACK : %d", gamestate.blackScore);
                                            textScoreBlack = TTF_RenderText_Blended(fontHacked,strScoreBlack, colorFont2);

                                            if(gamestate.blackScore == 0)
                                            {
                                                bAccept->state = 0;
                                                curState = SENDGAME;
                                                j1GlobalScore += gamestate.stake; // BLACK
                                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"BLACK won !", colorFont2);
                                            }
                                            else if(j1Tries > 3)
                                            {
                                                bAccept->state = 0;
                                                curState = SENDGAME;
                                                j2GlobalScore += gamestate.stake; // WHITE
                                                textCurPlayer = TTF_RenderText_Blended(fontHacked,"WHITE won !", colorFont1);
                                            }
                                            else
                                            {
                                                bAccept->state = 0;
                                                bRollDices->state = 1;
                                                bDoubleStack->state = 1;
                                                curState = SDOUBLESTACK;
                                                curPlayer = WHITE;
                                            }
                                          
                                        }
                                    }
                                }
                            }

                            // Détection de clic sur le bouton RollDices
                            if(((event.button.x >= bRollDices->rectButton.x) && (event.button.x <= bRollDices->rectButton.x + bRollDices->rectButton.w)) && ((event.button.y >= bRollDices->rectButton.y) && (event.button.y <= bRollDices->rectButton.y + bRollDices->rectButton.h)))
                            {
                                if(bRollDices->state==1) // Si le bouton est activé
                                {
                                    curState = SROLLDICES;
                                    bRollDices->state = 0;
                                    bDoubleStack->state = 0; 
                                }
                            }

                            printf("mouse position2 : %d %d diffX : %d diffY : %d\n",event.button.x,event.button.y,event.button.x-lastX,event.button.y-lastY);
                            lastX =  event.button.x;
                            lastY =  event.button.y;


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


            }


        //}


        /* ***************************
         *                           *
         *    DESSIN DES SURFACES    *
         *                           *
         * **************************/

        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        /*SDL_FillRect(screen, &bRollDices->rectButton, SDL_MapRGB(screen->format, 255, 0, 0));
        
        SDL_FillRect(screen, &bAccept->rectButton, SDL_MapRGB(screen->format, 255, 0, 0));
        
        SDL_FillRect(screen, &bDoubleStack->rectButton, SDL_MapRGB(screen->format, 255, 0, 0));*/

        drawButton(bRollDices, screen, t, bRTextSurf);

        drawButton(bAccept, screen, t, bATextSurf);

        drawButton(bDoubleStack, screen, t, bDTextSurf);

        SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);

        SDL_BlitSurface(title,0,screen, &fontPosTitle);

        SDL_BlitSurface(textDices,0,screen, &fontPosDices);

        SDL_BlitSurface(textCurPlayer,0,screen, &fontPosCurPlayer);

        SDL_BlitSurface(textScoreWhite,0,screen, &fontPosScoreWhite);

        SDL_BlitSurface(textScoreBlack,0,screen, &fontPosScoreBlack);

        drawDames(damesTab,dameWsurf,dameBsurf,screen,30);

        SDL_UpdateWindowSurface(window);


        SDL_Delay(17); // delay de 15 ms 

        t++;
        if(t>60) // car 60 images/s (SDL_Delay à 17 ms)
        {
            t = 0;
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
    free(hitboxesTab);
    free(j1NomLib);
    free(j2NomLib);
    free(bRollDices);
    free(bAccept);
    free(bDoubleStack);

    printf("Exited cleanly\n");
    return 0;
}



