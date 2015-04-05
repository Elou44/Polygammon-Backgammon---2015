#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>

void setScore(SGameState* gamestate){

    unsigned int i, scoreB = 0, scoreW = 0;
    for(i = 0; i < 24; i++)
    {
        if(gamestate->board[i].owner == WHITE)
        {
            scoreW += (unsigned int) gamestate->board[i].nbDames * (unsigned int) (24-i);
        }
        else
        {
            scoreB += (unsigned int) gamestate->board[i].nbDames * (unsigned int) (i+1);
        }

    }

    scoreW += (unsigned int) gamestate->bar[1] * 25; // on compte les pions qui sont dans la bar
    scoreB += (unsigned int) gamestate->bar[0] * 25;

    gamestate->whiteScore = scoreW;
	gamestate->blackScore = scoreB;

}

void setScore2(SGameState* gamestate){
    int i,j1,j2,w=0,b=0;

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
			w+=(25*gamestate->out[0]); // White correspont à l'indice 1 | il fallait prendre en compte la bar pas le out
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

	//on va utiliser whiteScore et blackScore
	gamestate->whiteScore = w;
	gamestate->blackScore = b;
}

void setColor(int i, int z, Dame *damesTab,const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf)
{
    if(gamestate->board[i].owner == WHITE)
    {
	damesTab[z].color=0;
    }
    else
    {
	damesTab[z].color=1;
    }
}

void setDamesPos(Dame *damesTab, const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf){
    //SDL_UnlockSurface(dameWsurf);
    //SDL_UnlockSurface(dameBsurf);
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
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;


            }
        }

        else if(i==1){

            printf("il y a %d dame(s) sur %d",gamestate->board[i].nbDames,i);

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 849;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==2){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 773;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==3){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 696;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==4){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 621;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==5){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 543;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;

            }

        }

        else if(i==6){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==7){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }


        else if(i==8){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==9){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==10){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==11){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y -= esp;
            }

        }

        else if(i==12){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==13){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==14){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==15){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==16){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==17){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==18){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 543;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==19){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 621;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==20){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 696;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==21){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 773;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==22){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 849;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                y += esp;
            }

        }

        else if(i==23){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 925;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
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



void drawDames(Dame *damesTab,SDL_Surface* dameWsurf, SDL_Surface* dameBsurf, SDL_Surface* screen, int nbDames)
{
    int i;

    //SDL_Rect dstrect;
    for(i = 0; i < nbDames ; i++)
    {

        if(damesTab[i].color == 0)
        {
            SDL_BlitSurface(dameWsurf,0,screen, damesTab[i].rectDame);
        }
        else
        {
            SDL_BlitSurface(dameBsurf,0,screen, damesTab[i].rectDame);
        }

    }
}

void initDamesTab(Dame *damesTab, int nbDames)
{
    int i;
    for(i = 0; i < nbDames; i++)
    {
      damesTab[i].rectDame = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectDame
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

        //SDL_FillRect(screen, hitboxesTab[i].rectHB, SDL_MapRGB(screen->format, 255, 0, 0));

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
