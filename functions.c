#include "functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <math.h>

//Update l'affiche du score des deux players
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
	    //Black
            scoreB += (unsigned int) gamestate->board[i].nbDames * (unsigned int) (i+1);
        }

    }

    scoreW += (unsigned int) gamestate->bar[1] * 25; // on compte les pions qui sont dans la bar
    scoreB += (unsigned int) gamestate->bar[0] * 25;

    gamestate->whiteScore = scoreW;
    gamestate->blackScore = scoreB;

}

//Update le propri�taire de chaque square apres chaque move
void setColor(int i, int z, Dame *damesTab,const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf)
{
    if(gamestate->board[i].owner == WHITE)
    {
        damesTab[z].color=1;
        //printf("setColor color=1 z: %d  \n",z);
    }
    else
    {
        damesTab[z].color=0;
        //printf("setColor color=0 z: %d  \n",z);

    }
}
//Initialisation de la position des pions sur l'�cran
void setDamesPos(Dame *damesTab, const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf){

    int i,j,x = 0, y = 615, y1 = 380, y2 = 23, y3 = 260, y4 = 600, z = 0, esp=40;


    for (i=0;i<24;i++){
	//partie bas du board
        if(i >=0 && i <= 11){

            y = 615;

        }
        else {
	//partie haut du board
            y = 27;

        }

        if (i==0){

            //printf("il y a %d dame(s) sur %d",gamestate->board[i].nbDames,i);
	        // i designe l'indice des squares et j designe le numero d'un pion
            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 948;
                damesTab[z].rectDame->y = y;
		
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
		        //on va diminuer la distance qui separe chaque pions sur un square en fonctions du nombre de pions present sur ce meme square
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }



            }
        }
        
        else if(i==1){

            //printf("il y a %d dame(s) sur %d",gamestate->board[i].nbDames,i);

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 872;
                damesTab[z].rectDame->y = y;

                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;

                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }

            }

        }

        else if(i==2){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 796;
                damesTab[z].rectDame->y = y;

                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }

            }

        }

        else if(i==3){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 719;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }

            }

        }

        else if(i==4){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 644;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }

            }

        }

        else if(i==5){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 566;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }

            }

        }

        else if(i==6){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }

        else if(i==7){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }


        else if(i==8){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }

        else if(i==9){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }

        else if(i==10){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }

        else if(i==11){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y -= 225 / gamestate->board[i].nbDames;
                }
                else{
                    y -= esp;
                }
            }

        }

        else if(i==12){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 35;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==13){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 112;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==14){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 187;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==15){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 264;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==16){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 340;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==17){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 416;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==18){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 566;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==19){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 644;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==20){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 719;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==21){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 796;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==22){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 872;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

        else if(i==23){

            for (j=0; j < gamestate->board[i].nbDames ; j++){
                damesTab[z].rectDame->x = 948;
                damesTab[z].rectDame->y = y;
                setColor(i,z,damesTab,gamestate,dameWsurf,dameBsurf);
                z++;
                if(gamestate->board[i].nbDames>5)
                {
                    y += 225 / gamestate->board[i].nbDames;
                }
                else{
                    y += esp;
                }
            }

        }

    }


        //24 bar noir milieu

        //printf("gamestate->bar[0]: %d\n",gamestate->bar[0]);
        //printf("gamestate->bar[1]: %d\n",gamestate->bar[1]);
        //printf("gamestate->out[0]: %d\n",gamestate->out[0]);
        //printf("gamestate->out[1]: %d\n",gamestate->out[1]);

    //initialisation de la position des pions pour les bars
    for (j=0; j < gamestate->bar[0] ; j++){
        damesTab[z].rectDame->x = 491;
        damesTab[z].rectDame->y = y3;
        damesTab[z].color=0;
        z++;
        if(gamestate->bar[0]>5)
        {
            y3 -= 225 / gamestate->bar[0];
        }
        else{
            y3 -= esp;
        }
    }

	//25 bar blanc


    for (j=0; j < gamestate->bar[1] ; j++){
        damesTab[z].rectDame->x = 491;
        damesTab[z].rectDame->y = y1;
        damesTab[z].color=1;
        z++;
        if(gamestate->bar[1]>5)
        {
            y1 += 225 / gamestate->bar[1];
        }
        else{
            y1 += esp;
        }

    }


	//26 out win noir

    for (j=0; j < gamestate->out[0] ; j++){
        damesTab[z].rectDame->x = 1048;
        damesTab[z].rectDame->y = y4;
        damesTab[z].color=0;
        z++;
        y4 -= 15;
    }


	//27 out win blanc

    for (j=0; j < gamestate->out[1] ; j++){
        damesTab[z].rectDame->x = 1048;
        damesTab[z].rectDame->y = y2;
        damesTab[z].color=1;
        z++;
        y2 += 15;
    }

}

void initGameState(SGameState* gamestate){

    //initialisation du plateau pour chaque debut de partie

    gamestate->stake = 1;

    int i;
    Square temp;

    for( i = 0; i < 24; i++) 
    // Initialisation de tous les squares � NOBODY et 0 dame
    {
        temp.nbDames = 0;
        temp.owner = NOBODY;
        gamestate->board[i] = temp;
    }

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

	gamestate->bar[0]=0;
	gamestate->bar[1]=0;

	gamestate->out[0]=0;
	gamestate->out[1]=0;

}



void drawDames(Dame *damesTab,SDL_Surface* dameWsurf, SDL_Surface* dameBsurf, SDL_Surface* screen, int nbDames)
{
    int i;

    //SDL_Rect dstrect;
    for(i = 0; i < nbDames ; i++)
    {

        if(damesTab[i].color == 1) // WHITE
        {
            SDL_BlitSurface(dameWsurf,0,screen, damesTab[i].rectDame);

        }
        else // BLACK
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

//fonction qui va permettre de deplacer un pion d'un square a un autre
void initHitBoxesTab(Hitbox *hitboxesTab, int nbHB, SDL_Surface* screen)
{

    int i,y1 = 380, y2= 23, width1 = 68, height = 300;


    for(i = 0; i < 28; i++){

        hitboxesTab[i].rectHB = (SDL_Rect*) malloc (1*sizeof(SDL_Rect)); // PENSER A LIBERER LE rectHB

        if(i == 0)
        {
            hitboxesTab[i].rectHB->x = 945;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 1)
        {
            hitboxesTab[i].rectHB->x = 869;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 2)
        {
            hitboxesTab[i].rectHB->x = 793;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 3)
        {
            hitboxesTab[i].rectHB->x = 717;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 4)
        {
            hitboxesTab[i].rectHB->x = 641;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 5)
        {
            hitboxesTab[i].rectHB->x = 563;
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
            hitboxesTab[i].rectHB->x = 563;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 19)
        {
            hitboxesTab[i].rectHB->x = 641;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 20)
        {
            hitboxesTab[i].rectHB->x = 717;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 21)
        {
            hitboxesTab[i].rectHB->x = 793;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 22)
        {
            hitboxesTab[i].rectHB->x = 869;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }

        else if(i == 23)
        {
            hitboxesTab[i].rectHB->x = 945;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
        }
	//bar noir
	else if (i == 24)
	{
	    hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
	}
	//bar blanc
	else if (i == 25)
	{
            hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
	}
	//out blanc
	else if (i == 26)
	{
            hitboxesTab[i].rectHB->x = 1045;
            hitboxesTab[i].rectHB->y = 13;
            hitboxesTab[i].rectHB->w = 78;
            hitboxesTab[i].rectHB->h = 284;
	}
	//out noir
	else if (i == 27)
	{
            hitboxesTab[i].rectHB->x = 1045;
            hitboxesTab[i].rectHB->y = 383;
            hitboxesTab[i].rectHB->w = 78;
            hitboxesTab[i].rectHB->h = 284;
	}

       //SDL_FillRect(screen, hitboxesTab[i].rectHB, SDL_MapRGB(screen->format, 255, 0, 0)); //Pour afficher les hitboxes

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
                //printf("click detected on hitbox %d\n", i);
                return i;
            }
        }
    }
    printf("no hitbox detected\n");
    return -1;

}

void rollDices(unsigned char* dices)
{

    dices[0] =  rand()%6+1;
    dices[1] =  rand()%6+1;

}



//fonction qui va permettre de mettre a jour le board apres chaque moves
void updateSGameState(SGameState* gamestate, SMove *moves,unsigned int *nbMoves, Player curPlayer){
 int i;
//notre fonction suppose que tous les moves qui lui sont transmis sont valides
 for (i=0;i < *nbMoves;i++){
        //cas depuis un square vers un autre
        if ((moves[i].dest_point != 0 && moves[i].dest_point !=25) && (moves[i].src_point > 0 && moves[i].src_point < 25)){

              if(gamestate->board[moves[i].dest_point-1].owner == curPlayer || gamestate->board[moves[i].dest_point-1].owner == NOBODY)
              {

        	       gamestate->board[moves[i].dest_point-1].nbDames += 1;

              }
              else if(gamestate->board[moves[i].dest_point-1].owner != curPlayer) // si on mange un pion de l'adversaire ou on capture une nouvelle case
              {
                    if(curPlayer == WHITE)
                    {
                        gamestate->bar[0] += 1; // on rajoute un pion dans la bar du noir
                    }
                    else if(curPlayer == BLACK)
                    {
                        gamestate->bar[1] += 1; // on rajoute un pion dans la bar du noir
                    }
        	        
              }

              gamestate->board[moves[i].src_point-1].nbDames -= 1;
              gamestate->board[moves[i].dest_point-1].owner = curPlayer;


        }

            //cas depuis bar vers square
            else if (moves[i].src_point == 0 && (moves[i].dest_point < 25 && moves[i].dest_point > 0)){


                if(gamestate->board[moves[i].dest_point-1].owner == curPlayer || gamestate->board[moves[i].dest_point-1].owner == NOBODY) // si on mange un pion de l'adversaire ou on capture une nouvelle case
                {

                    gamestate->board[moves[i].dest_point-1].nbDames += 1;

                }
                else if(gamestate->board[moves[i].dest_point-1].owner != curPlayer)
                {

                    if(curPlayer == WHITE)
                    {
                        gamestate->bar[0] += 1; // on rajoute un pion dans la bar du noir
                    }
                    else if(curPlayer == BLACK)
                    {
                        gamestate->bar[1] += 1; // on rajoute un pion dans la bar du noir
                    }
                }

                if(curPlayer == WHITE)
                {
                    gamestate->bar[1] -= 1;
                }
                else if(curPlayer == BLACK)
                {
                    gamestate->bar[0] -= 1;
                }
                
                gamestate->board[moves[i].dest_point-1].owner = curPlayer;

          }
        //cas depuis square vers out
        else if (moves[i].dest_point == 25 && (moves[i].src_point < 25 && moves[i].src_point > 0)){

           if (curPlayer == WHITE){

                gamestate->out[1] += 1;
                gamestate->board[moves[i].src_point-1].nbDames -= 1;
           }
           else if (curPlayer == BLACK){

                gamestate->out[0] += 1;
                gamestate->board[moves[i].src_point-1].nbDames -= 1;
           }
        }
    }

    for (i=0;i < 24;i++) // remettre � NOBODY les squares vides
    {
        if(gamestate->board[i].nbDames == 0) gamestate->board[i].owner = NOBODY;
        //printf("proprio yop : i:%d %d\n", i,gamestate->board[i].owner);
    }

}



void clickToSMoves(int* indiceHBTab, SMove* moves,unsigned int *nbMoves, Player curPlayer)
{
    if(*nbMoves < 4)
    {
        int i; // normalisation des indices

        for (i = 0; i < 2; i++)
        {
            if(indiceHBTab[i]>=0 && indiceHBTab[i] <= 23) indiceHBTab[i] += 1;
            else if(indiceHBTab[i] == 24 || indiceHBTab[i] == 25) indiceHBTab[i] = 0;
            else if(indiceHBTab[i] == 26 || indiceHBTab[i] == 27) indiceHBTab[i] = 25;
        }

        printf("indiceHBTab[0] %d | indiceHBTab[1] %d | nbMoves %d\n",indiceHBTab[0],indiceHBTab[1], *nbMoves);

        moves[*nbMoves].src_point = indiceHBTab[0];
        moves[*nbMoves].dest_point = indiceHBTab[1];

        printf("moves added between %d and %d\n",moves[*nbMoves].src_point,moves[*nbMoves].dest_point);
        *nbMoves += 1; // on incr�mente le compteur de moves
        indiceHBTab[0] = -1;
        indiceHBTab[1] = -1;
    }

    else
    {
        printf("erreur segmentation fault out of SMoves[4]");
    }
}


int arbitre(SGameState gamestate, Player curPlayer, int nbMoves, SMove* move, unsigned char* dices)
{
    
    /******************************************************
    **                                                   **
    **   d�claration et initialisation des param�tres    **
    **                                                   **
    ******************************************************/
    
    SGameState curGameState;    //on cr�� une copie du gamestate, on aurait pu directement utiliser le gamestate utilis� en parametre
    curGameState = gamestate;   //mais on avait utilis� un pointeur vers le gamestate � la base (d'o� la copie) mais pour une raison obscure cel� ne fonctionnait pas (copie vide et valeur point�e erron�e)

    SMove curMove;              //mouvement courant, en cours d'�tude

    int i, j, l;                //variables de boucle
    int dist;                   //distance entre le point de d�part et d'arriv�e du mouvement courant
    int nbDices;                //nombre de d�s � jouer
    int usedDices;              //variable pour �valuer l'utilisation d'un d�
    int totDames;               //variable pour �valuer le nombre de dames restantes sur le plateau (utilis�e pour voir si l'on peut sortir ses pions ou non)
    int sens;                   //sens du mouvement (on ne peut pas reculer)

    
    /******************************************************
    **                                                   **
    **           d�termination du nombre de d�s          **
    **                                                   **
    ******************************************************/
    
    if(dices[0] == dices[1])
    {
        nbDices = 4;        //on d�finit le nombre de d�s � jouer en fonction que ce soit un double (4) ou non (2);
    } else {
        nbDices = 2;
    }

    
    /******************************************************
    **                                                   **
    **d�termination du nombre de coups maximums possibles**
    **                                                   **
    ******************************************************/
    
    int nbPot = 0;
    SMove potMove;
    
    if (nbPot < nbDices)
    {
                            //pas trait� car pas trouv� comment g�n�rer tous les mouvements possibles
                            //dans l'id�e je voulais compter s'il y avait autant de mouvements possibles que de d�s � jouer pour �viter les mouvements bloquants
                            //je voulais aussi d�finir une somme des d�s utilis�s pour faire les mouvements afin de voir, dans le cas o� le nombre de mouvements potentiels nbPot
                            //soit inferieur au nombre de d�s apr�s avoir parcourru tous les mouvements, si la valeur des d�s �tait maximis�e (pr�f�rer utiliser un 6 qu'un 3)
    }
    
    
    
    /******************************************************
    **                                                   **
    **      d�termination de la validit� des coups       **
    **                                                   **
    ******************************************************/
    
    for(i=0;i<nbMoves;i++)
    {
        curMove = move[i];
        if (curMove.dest_point == 25 && curPlayer == WHITE)
        {
            dist = 25 - curMove.src_point;
        }
        else if (curMove.src_point == 0 && curPlayer == BLACK)      //si notre mouvement est un mouvement particulier (partant du bar ou arrivant dans le out)
        {                                                           //on calcule la distance differemment pour s'adapter aux cases du plateau (out = 25 et bar = 0 dans tous les cas)
            dist = 25 - curMove.dest_point;
        } 
        else if (curMove.dest_point == 25 && curPlayer == BLACK)
        {
            dist = curMove.src_point;
        }
        else if (curMove.src_point == 0 && curPlayer == WHITE)
        {
            dist = 25 - curMove.dest_point;
        }
        else 
        {
            dist = abs(curMove.dest_point - curMove.src_point);     //si on est dans un mouvement normal, on calcule la distance par la valeur absolue de la diff�rence
        }




        for(j=0;j<nbDices;j++)                              
        {
            printf("De : %d \n",dices[j]);                          //prints des d�s et de la distance
            printf("dist : %d\n", dist);
            if(dices[j] == dist)
                {
                    dices[j] = 0;                                   //si un d� correspond � la distance on incr�mente usedDices et on arr�te la boucle
                    usedDices++;
                    break;
                }
        }

        if (usedDices < 1)                                          //si aucun d� n'a pu �tre utilis� on renvoie une erreur
        {
            printf("Il faut utiliser les d�s !\n");
            return(0);
        }




        printf("curPlayer : %d\n",curPlayer);                                           //print du joueur en cours, 0 = BLACK, 1 = WHITE
        if (curMove.src_point == 0)                                                     
        {                                                                               //si on se d�place depuis le bar
            printf("owner : %d\n",curPlayer);                                           //le proprietaire est le joueur courant
            printf("nbdames : %d\n", curGameState.bar[curPlayer]);                      //le nombre de dames et le contenu de son bar
        }                                                                               //cette conditionnelle permet d'�viter un core dumped dans le cas du mouvement partant du bar
        else                                                                            //(board[-1] --> core dumped)
        {
        printf("owner : %d\n",curGameState.board[curMove.src_point-1].owner);           //sinon le propri�taire est celui de la case de d�part
        printf("nbdames : %d\n",curGameState.board[curMove.src_point-1].nbDames);       //et le nombre de dames celui de la case de d�part aussi
        }
       
        printf("src_point : %d\n", curMove.src_point);                                  //prints des extremit�s du mouvement courant
        printf("dest_point : %d\n", curMove.dest_point);






        if (curMove.src_point !=0)
        {
            if (curGameState.board[curMove.src_point-1].owner != curPlayer )        //si je ne suis pas le propri�taire de la source
            {                                                                       //on renvoie une erreur
                printf("Il faut bouger ses propres pions !\n");
                return(0);
            }
        }





        if (curMove.src_point != 0 && curGameState.bar[curPlayer] != 0)             //si j'effectue un mouvement avant de sortir mon pion du bar
        {                                                                           //on renvoie une erreur
            printf("Il faut sortir les pions du bar avant tout !\n");
            return(0);
        }





        if (curGameState.board[curMove.dest_point-1].owner != curPlayer && curGameState.board[curMove.dest_point-1].nbDames > 1)        //si je me d�place sur une case adverse possedant + d'une dame
        {                                                                                                                               //on renvoie erreur
            printf("Il faut d�placer les pions sur des cases libres ou des blots\n");
            return(0);
        }




        
        if (curPlayer == WHITE)                                                     //si le joueur est blanc
        {
            if (curMove.src_point == 0)                                             //on d�finit les diff�rents sens pour les cas extremes et le cas g�n�ral
            {
                sens = curMove.dest_point;
            }
            else if (curMove.dest_point == 25)
            {
                sens = 25 - curMove.src_point;
            }
            else
            {
                sens = curMove.dest_point - curMove.src_point;
            }
            
            printf("sens : %d\n", sens);                                            //print du sens

            if (sens < 0)                                                           //si le sens n'est pas bon on renvoie erreur
            {
                printf("Il faut aller dans le bon sens joueur blanc !\n");          
                return(0);
            }
        }
        




        if (curPlayer == BLACK)                                                     //idem pour le joueur noir
        {
            
            if (curMove.src_point == 0)
            {
                sens = curMove.dest_point - 25;
            }
            else if (curMove.dest_point == 25)
            {
                sens = curMove.src_point - 25;
            }
            else 
            {
                sens = curMove.dest_point - curMove.src_point;

            }

            printf("sens : %d\n", sens);
            if (sens > 0)
            {
                printf("Il faut aller dans le bon sens joueur noir !\n");
                return(0);
            }
        }
        




        totDames = 0;                                                                                   //on fixe le total des dames � 0
        
        if (curPlayer == WHITE && curMove.dest_point == 25)
        {
            for(l=18;l<24;l++)                                                                          //on compte les pions sur le jan interieur du joueur blanc
            {
                if(curGameState.board[l].owner == curPlayer)
                {
                    totDames += curGameState.board[l].nbDames;
                }
            }
            if (totDames + curGameState.out[curPlayer] != 15)                                           //si ses 15 pions ne sont pas dans son jan interieur + son out
            {                                                                                           //on renvoie erreur
                printf("Il faut avoir tous ses pions dans son jan interieur pour les sortir !\n");
                return(0);
            }
        }




        
        if (curPlayer == BLACK && curMove.dest_point == 25)                                             //idem pour le noir
        {
            for(l=0;l<6;l++)
            {
                if(curGameState.board[l].owner == curPlayer)
                {
                    totDames += curGameState.board[l].nbDames;
                }
            }
            if (totDames + curGameState.out[curPlayer] != 15)
            {
                printf("Il faut avoir tous ses pions dans son jan interieur pour les sortir !\n");
                return(0);
            }
        }


    

    /******************************************************
    **                                                   **
    **        mise � jour du gamestate provisoire        **
    **                                                   **
    ******************************************************/

        unsigned int nbValidMoves = 1;
        SMove validMove[1];
        validMove[0] = curMove;
        updateSGameState(&curGameState, validMove, &nbValidMoves, curPlayer);

    }


    return(1);
}


void drawButton(Button *button, SDL_Surface *screen,unsigned int t, SDL_Surface *surfText)
{
    // Calcul du d�calage de couleur
    int x; 
    if(t<30) x = t;
    else if(t>=30) x = 60 - t;
    x = (int) x*1.5;
  

    if(button->state == 0) // Si le bouton est d�sactiv�
    {
        SDL_FillRect(screen, &button->rectButton, SDL_MapRGB(screen->format, 156, 156, 156));
    }
    else if(button->state == 1) // Si le bouton est activ�
    {
        SDL_FillRect(screen, &button->rectButton, SDL_MapRGB(screen->format, 82, 177+x, 185));
    }


    SDL_BlitSurface(surfText,0,screen, &button->rectText);
    
}

void freeHitBoxes(Hitbox *hitboxesTab)
{
    int i;
    for (i=0;i<28;i++)
    {
      free(hitboxesTab[i].rectHB);
    }

}

void freeDamesTab(Dame *damesTab, int nbDames)
{
   int i;
   for (i=0; i<nbDames; i++)
   {
     free(damesTab[i].rectDame);
   }
}        

        
void scoreLog(int j1ScoreGlobal, int j2ScoreGlobal)
{
    FILE* fichier;
    fichier = NULL;

    fichier = fopen("log.txt", "a+");

    if (fichier != NULL)
    {
        fprintf(fichier,"Le joueur 1 (BLACK) a %d points // Le joueur 2 (WHITE) a %d points\n", j1ScoreGlobal, j2ScoreGlobal);
        fclose(fichier);
    }
    else
    {
        printf("Fichier introuvable.\n");
    }
}