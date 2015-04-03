#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "functions.h"

#define OS 1 // 0 = Windows | 1 = Linux

#if OS == 0
   #include <windows.h>
#elif OS == 1
   #include <dlfcn.h>
#endif

// Include Windows //


//variable globale

SGameState gamestate;

void setScore(SGameState *gamestate){
    int i,j1,j2,w=0,b=0;
//on va utiliser whiteScore et blackScore DU CACA
	gamestate->whiteScore = w;
	gamestate->blackScore = b;
	for (i=0;i<24;i++){
	   if (gamestate->board[i].owner == WHITE){
		   j1 = gamestate->board[i].nbDames;
		   if (i == 0){
			w+=24;
		   }
		   else if (i == 1){
			w+=(23*j1);
		   }
		   else if (i == 2){
			w+=(22*j1);
		   }
		   else if (i == 3){
			w+=(21*j1);
		   }
		   else if (i == 4){
			w+=(20*j1);
		   }
		   else if (i == 5){
			w+=(19*j1);
		   }
		   else if (i == 6){
			w+=(18*j1);
		   }
		   else if (i == 7){
			w+=(17*j1);
		   }
		   else if (i == 8){
			w+=(16*j1);
		   }
		   else if (i == 9){
			w+=(15*j1);
		   }
		   else if (i == 10){
			w+=(14*j1);
		   }
		   else if (i == 11){
			w+=(13*j1);
		   }
		   else if (i == 12){
			w+=(12*j1);
		   }
		   else if (i == 13){
			w+=(11*j1);
		   }
		   else if (i == 14){
			w+=(10*j1);
		   }
		   else if (i == 15){
			w+=(9*j1);
		   }
		   else if (i == 16){
			w+=(8*j1);
		   }
		   else if (i == 17){
			w+=(7*j1);
		   }
		   else if (i == 18){
			w+=(6*j1);
		   }
		   else if (i == 19){
			w+=(5*j1);
		   }
		   else if (i == 20){
			w+=(4*j1);
		   }
		   else if (i == 21){
			w+=(3*j1);
		   }
		   else if (i == 22){
			w+=(2*j1);
		   }
		   else if (i == 23){
			w+=(1*j1);
		   }
		   //pour le out
		   else if (i == 24){
			w+=(25*gamestate->out[0]);
		   }
	   }
	   else if (gamestate->board[i].owner == BLACK){
		   j2 = gamestate->board[i].nbDames;
		   if (i == 23){
			w+=24;
		   }
		   else if (i == 22){
			b+=(23*j2);
		   }
		   else if (i == 21){
			b+=(22*j2);
		   }
		   else if (i == 20){
			b+=(21*j2);
		   }
		   else if (i == 19){
			b+=(20*j2);
		   }
		   else if (i == 18){
			b+=(19*j2);
		   }
		   else if (i == 17){
			b+=(18*j2);
		   }
		   else if (i == 16){
			b+=(17*j2);
		   }
		   else if (i == 15){
			b+=(16*j2);
		   }
		   else if (i == 14){
			b+=(15*j2);
		   }
		   else if (i == 13){
			b+=(14*j2);
		   }
		   else if (i == 12){
			b+=(13*j2);
		   }
		   else if (i == 11){
			b+=(12*j2);
		   }
		   else if (i == 10){
			b+=(11*j2);
		   }
		   else if (i == 9){
			b+=(10*j2);
		   }
		   else if (i == 8){
			b+=(9*j2);
		   }
		   else if (i == 7){
			b+=(8*j2);
		   }
		   else if (i == 6){
			b+=(7*j2);
		   }
		   else if (i == 5){
			b+=(6*j2);
		   }
		   else if (i == 4){
			b+=(5*j2);
		   }
		   else if (i == 3){
			b+=(4*j2);
		   }
		   else if (i == 2){
			b+=(3*j2);
		   }
		   else if (i == 1){
			b+=(2*j2);
		   }
		   else if (i == 0){
			b+=(1*j2);
		   }
		   //pour le out
		   else if (i == 25){
			b+=(25*gamestate->out[1]);
		   }
	   }
	}	
}

void setSurf(int i, int z, Dame *damesTab, SGameState* gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf)
{
    if(gamestate->board[i].owner == WHITE)
    {
	damesTab[z].coulor=0;
	damesTab[z].dameSurf = dameWsurf;
    }
    else
    {
	damesTab[z].coulor=1;
	damesTab[z].dameSurf = dameBsurf;
    }
}

void setDamesPos(Dame *damesTab, SGameState* gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf){
    int i,j,x=0,y=615, z=0, esp=40;


    for (i=0;i<24;i++){
    y = 615;
        if(i >=0 && i <= 11){

            y = 615;

        }
        else {

            y = 20;

        }





        if (i==0){

            printf("il y a %d dame(s) sur %d",gamestate->board[i].nbDames,i);

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 925;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;


            }
        }

        else if(i==1){

            printf("il y a %d dame(s) sur %d",gamestate->board[i].nbDames,i);

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 849;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==2){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 773;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==3){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 696;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==4){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 621;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==5){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 543;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==6){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==7){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }


        else if(i==8){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==9){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==10){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==11){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==12){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==13){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==14){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==15){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==16){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==17){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==18){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 543;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==19){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 621;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==20){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 696;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==21){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 773;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==22){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 849;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==23){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 925;
                damesTab[z].rectDame->y = y;
		setSurf(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

    }
}

void initGameState(SGameState* gamestate){
	Square temp;
	temp.nbDames = 2;
	temp.owner = WHITE;
	gamestate->board[0] = temp;

	temp.nbDames = 5;
	temp.owner = BLACK;
	gamestate->board[5] = temp;

	temp.nbDames = 3;
	temp.owner = BLACK;
	gamestate->board[7] = temp;

	temp.nbDames = 5;
	temp.owner = WHITE;
	gamestate->board[11] = temp;

	temp.nbDames = 5;
	temp.owner = BLACK;
	gamestate->board[12] = temp;

	temp.nbDames = 3;
	temp.owner = WHITE;
	gamestate->board[16] = temp;

	temp.nbDames = 5;
	temp.owner = WHITE;
	gamestate->board[18] = temp;

	temp.nbDames = 2;
	temp.owner = BLACK;
	gamestate->board[23] = temp;
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

void initDamesTab(Dame *damesTab, int nbDames)
{
    int i;
    for(i = 0; i < nbDames; i++)
    {
      damesTab[i].rectDame = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectDame
      damesTab[i].dameSurf = (SDL_Surface*) malloc (1*sizeof(SDL_Surface)); // PENSER A LIBERER LA SURFACE

    }
}

void initHitBoxesTab(Hitbox *hitboxesTab, int nbHB, SDL_Surface* screen)
{

    int i,y1 = 380, y2= 23, width1 = 68, height = 300;


    for(i = 0; i < 28; i++){

        hitboxesTab[i].rectHB = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectHB

        if(i == 0)
        {
            hitboxesTab[i].rectHB->x = 922;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 1)
        {
            hitboxesTab[i].rectHB->x = 846;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 2)
        {
            hitboxesTab[i].rectHB->x = 770;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 3)
        {
            hitboxesTab[i].rectHB->x = 694;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 4)
        {
            hitboxesTab[i].rectHB->x = 618;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 5)
        {
            hitboxesTab[i].rectHB->x = 540;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 6)
        {
            hitboxesTab[i].rectHB->x = 414;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 7)
        {
            hitboxesTab[i].rectHB->x = 338;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 8)
        {
            hitboxesTab[i].rectHB->x = 262;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 9)
        {
            hitboxesTab[i].rectHB->x = 185;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 10)
        {
            hitboxesTab[i].rectHB->x = 108;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 11)
        {
            hitboxesTab[i].rectHB->x = 32;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 12)
        {
            hitboxesTab[i].rectHB->x = 32;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 13)
        {
            hitboxesTab[i].rectHB->x = 108;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 14)
        {
            hitboxesTab[i].rectHB->x = 185;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 15)
        {
            hitboxesTab[i].rectHB->x = 262;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 16)
        {
            hitboxesTab[i].rectHB->x = 338;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 17)
        {
            hitboxesTab[i].rectHB->x = 414;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 18)
        {
            hitboxesTab[i].rectHB->x = 540;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 19)
        {
            hitboxesTab[i].rectHB->x = 618;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 20)
        {
            hitboxesTab[i].rectHB->x = 694;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 21)
        {
            hitboxesTab[i].rectHB->x = 770;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 22)
        {
            hitboxesTab[i].rectHB->x = 846;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 23)
        {
            hitboxesTab[i].rectHB->x = 922;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }
	//out blanc
	else if (i == 24)
	{
	    hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = 44;
            hitboxesTab[i].rectHB->h = height;	    
	}
	//out noir
	else if (i == 25)
	{
            hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = 44;
            hitboxesTab[i].rectHB->h = height;	    
	}
	//win blanc
	else if (i == 26)
	{
            hitboxesTab[i].rectHB->x = 1015;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
	}
	//win noir
	else if (i == 27)
	{
            hitboxesTab[i].rectHB->x = 1015;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
	}

        SDL_FillRect(screen, hitboxesTab[i].rectHB, SDL_MapRGB(screen->format, 255, 0, 0));

    }


}





int detectClickIntoHitbox(Hitbox *hitboxesTab, int nbHB, int x, int y)
{
    int i;

    for(i = 0; i < 28; i++)
    {
        if((x >= hitboxesTab[i].rectHB->x) && (x <= hitboxesTab[i].rectHB->x + hitboxesTab[i].rectHB->w))
        {
            if((y >= hitboxesTab[i].rectHB->y) && (y <= hitboxesTab[i].rectHB->y + hitboxesTab[i].rectHB->h))
            {
                printf("click detected on hitbox %d\n", i);
                return i;
            }
        }
    }
    printf("no hitbox detected\n");
    return -1;

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


    int sWidth=1241, sHeigth=811;
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(sWidth, sHeigth, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);

    SDL_Surface *SDL_DisplayFormatAlpha(SDL_Surface *screen);
    if ( !screen )
    {
        printf("Unable to set 1241*811 video: %s\n", SDL_GetError());
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
    //init SDL TTF
    /*TTF_Init();
    //Si erreur
    if(TTF_Init() == -1)

    {

    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());

    exit(EXIT_FAILURE);

    }
    //Chargement de la police
    TTF_Font *police = NULL;
    police = TTF_OpenFont("./police/Modern Serif Italic.ttf",20);
	*/
    // centre the bitmap on screen


    srand(time(NULL));
    int i,j=0;
    Dame *damesTab = (Dame*) malloc (30*sizeof(Dame));
    initDamesTab(damesTab,30);

    // Initialisation des Hitboxes

    Hitbox *hitboxesTab = (Hitbox*) malloc (28*sizeof(Hitbox));
    SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
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





            // DRAWING STARTS HERE

            // clear screen
           // SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

            // DESSINER L'ECRAN

            /*SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
            drawDames(damesTab,screen,30);

            // DRAWING ENDS HERE

            // finally, update the screen :)
            SDL_Flip(screen);
            cpt++;
	   // printf("frame%d\n",cpt%100);
            SDL_Delay(10);*/
        }


            //SDL_BlitSurface(backgroundBoard,0,screen, &rectBoard);
            drawDames(damesTab,screen,30);

            // DRAWING ENDS HERE

            // finally, update the screen :)
            SDL_Flip(screen);
            cpt++;
	   // printf("frame%d\n",cpt%100);
            SDL_Delay(10);



    } // end main loop

    // LIBERATION DE LA MEMOIRE
    SDL_FreeSurface(dameBsurf);
    SDL_FreeSurface(dameWsurf);

    // all is well ;)
    free(damesTab);
    printf("Exited cleanly\n");
    return 0;
}
