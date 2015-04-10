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

//Update le propriétaire de chaque square apres chaque move
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
//Initialisation de la position des pions sur l'écran
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

    for( i = 0; i < 24; i++) // Initialisation de tous les squares à NOBODY et 0 dame
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

    for (i=0;i < 24;i++) // remettre à NOBODY les squares vides
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
        *nbMoves += 1; // on incrémente le compteur de moves
        indiceHBTab[0] = -1;
        indiceHBTab[1] = -1;
    }

    else
    {
        printf("erreur segmentation fault out of SMoves[4]");
    }
}


int arbitre(SGameState* gamestate, Player curPlayer, int nbMoves, SMove* move, unsigned char* dices)
{
    
    /******************************************************
    **                                                   **
    **   déclaration et initialisation des paramêtres    **
    **                                                   **
    ******************************************************/
    
    SGameState curGameState;
    curGameState = *gamestate;
    SMove curMove;
    int i,j,k,l,dist,nbDices,usedDices,totDames; /*unused k si on garde le commentaire plus bas*/

    
    
    
    /******************************************************
    **                                                   **
    **           détermination du nombre de dés          **
    **                                                   **
    ******************************************************/
    
    if(dices[0] == dices[1])
    {
        nbDices = 4;
    } else {
        nbDices = 2;
    }

    
    /******************************************************
    **                                                   **
    **détermination du nombre de coups maximums possibles**
    **                                                   **
    ******************************************************/
    
    int nbPot = 0;
    SMove potMove;
    
    if (nbPot < nbDices)
    {
        
    }
    
    
    
    /******************************************************
    **                                                   **
    **      détermination de la validité des coups       **
    **                                                   **
    ******************************************************/
    
    for(i=0;i<nbMoves;i++)
    {
        curMove = move[i];

        dist = abs(curMove.dest_point - curMove.src_point);
        totDames = 0;
        for(j=0;j<nbDices;j++)
        {
            if(dices[j] == dist)
                {
                    dices[j] = 0;
                    usedDices++;
                    break;
                }
            printf("Il faut utiliser les dés !");
            return(0);
            /*for(k=0;k<nbDices;k++)
            {
                if(k!=j)
                {
                    if(dices[j]+dices[k] == dist)
                    {
                        dices[j] = 0;
                        dices[k] = 0;
                        usedDices += 2;
                        break;
                    }
                    //à voir comment gérer le stockage des dés utilisés
                    printf("Il faut utiliser les dés !");
                    return(0);
                }
            }*/

        }

        if (curGameState.board[curMove.src_point].owner != curPlayer)
        {
            printf("Il faut bouger ses propres pions !");
            return(0);
        }

        if (curMove.src_point != 0 && curGameState.bar[curPlayer] != 0)
        {
            printf("Il faut sortir les pions du bar avant tout !");
            return(0);
        }

        if (curGameState.board[curMove.dest_point].owner != curPlayer && curGameState.board[curMove.dest_point].nbDames > 1)
        {
            printf("Il faut déplacer les pions sur des cases libres ou des blots");
            return(0);
        }
        
        if (curPlayer == WHITE)
        {
            if (curMove.dest_point - curMove.src_point < 0)
            {
                printf("Il faut aller dans le bon sens !");
                return(0);
            }
        }
        
        if (curPlayer == BLACK)
        {
            if (curMove.dest_point - curMove.src_point > 0)
            {
                printf("Il faut aller dans le bon sens !");
                return(0);
            }
        }
        
        
        if (curPlayer == WHITE)
        {
            for(l=19;l<25;l++)
            {
                if(curGameState.board[l].owner == curPlayer)
                {
                    totDames += curGameState.board[l].owner;
                }
            }
            if (totDames + curGameState.out[curPlayer] != 15)
            {
                printf("Il faut avoir tous ses pions dans son jan interieur pour les sortir !");
                return(0);
            }
        }
        
        if (curPlayer == BLACK)
        {
            for(l=1;l<7;l++)
            {
                if(curGameState.board[l].owner == curPlayer)
                {
                    totDames += curGameState.board[l].owner;
                }
            }
            if (totDames + curGameState.out[curPlayer] != 15)
            {
                printf("Il faut avoir tous ses pions dans son jan interieur pour les sortir !");
                return(0);
            }
        }
        
        
    

    /******************************************************
    **                                                   **
    **        mise à jour du gamestate provisoire        **
    **                                                   **
    ******************************************************/
        
        curGameState.board[curMove.src_point].nbDames--;
        if (curGameState.board[curMove.src_point].nbDames == 0) /*si la case de départ n'a plus de dames elle devient neutre*/
        {
            curGameState.board[curMove.src_point].owner = -1;
        }

        if (curGameState.board[curMove.dest_point].owner != curPlayer) /*si la case d'arrivée ne m'appartient pas, elle m'appartient*/
        {
            curGameState.board[curMove.dest_point].owner = curPlayer;

            if (curGameState.board[curMove.dest_point].nbDames != 1)/*si aucune dame n'est présente on en ajoute une*/
            {
                curGameState.board[curMove.dest_point].nbDames++;
            }
        }
        
        /*unsigned int nbvalidmove = 1;
        SMove validMove[1];
        validMove[0] = curMove;
        updateSGameState(&curGameState, validMove, &nbValidMoves, curPlayer);*/

    }


    return(1);
}


void drawButton(Button *button, SDL_Surface *screen,unsigned int t, SDL_Surface *surfText)
{
    // Calcul du décalage de couleur
    int x; 
    if(t<30) x = t;
    else if(t>=30) x = 60 - t;
    x = (int) x*1.5;
  

    if(button->state == 0) // Si le bouton est désactivé
    {
        SDL_FillRect(screen, &button->rectButton, SDL_MapRGB(screen->format, 156, 156, 156));
    }
    else if(button->state == 1) // Si le bouton est activé
    {
        SDL_FillRect(screen, &button->rectButton, SDL_MapRGB(screen->format, 82, 177+x, 185));
    }


    SDL_BlitSurface(surfText,0,screen, &button->rectText);
    
}
