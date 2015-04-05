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


void setColor(int i, int z, Dame *damesTab,const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf)
{
    if(gamestate->board[i].owner == WHITE)
    {
        damesTab[z].color=1;
        printf("setColor color=1 z: %d  \n",z);
    }
    else
    {
        damesTab[z].color=0;
        printf("setColor color=0 z: %d  \n",z);

    }
}

void setDamesPos(Dame *damesTab, const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf){
    //SDL_UnlockSurface(dameWsurf);
    //SDL_UnlockSurface(dameBsurf);
    int i,j,x = 0, y = 615, y1 = 380, y2 = 23, z = 0, esp=40;


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


    //24 bar noir milieu

        printf("gamestate->bar[0]: %d\n",gamestate->bar[0]);
        printf("gamestate->bar[1]: %d\n",gamestate->bar[1]);
        printf("gamestate->out[0]: %d\n",gamestate->out[0]);
        printf("gamestate->out[1]: %d\n",gamestate->out[1]);
    for (j=0; j < gamestate->bar[0] ; j++){
        damesTab[z].rectDame->x = 500;
        damesTab[z].rectDame->y = y2;
        damesTab[z].color=0;
        z++;
        y2 += esp;
    }

	//25 bar blanc


    for (j=0; j < gamestate->bar[1] ; j++){
        damesTab[z].rectDame->x = 500;
        damesTab[z].rectDame->y = y1;
        damesTab[z].color=1;
        z++;
        y1 += esp;
    }


	//26 out win blanc

    for (j=0; j < gamestate->out[0] ; j++){
        damesTab[z].rectDame->x = 1015;
        damesTab[z].rectDame->y = y2;
        damesTab[z].color=1;
        z++;
        y2 += esp;
    }


	//27 out win noir

    for (j=0; j < gamestate->out[1] ; j++){
        damesTab[z].rectDame->x = 1015;
        damesTab[z].rectDame->y = y1;
        damesTab[z].color=0;
        z++;
        y1 += esp;
    }

}

void initGameState(SGameState* gamestate){


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
            //printf("color = 1, damesTab[%d].rectDame %d %d\n",i,damesTab[i].rectDame->x,damesTab[i].rectDame->y);
        }
        else // BLACK
        {
            SDL_BlitSurface(dameBsurf,0,screen, damesTab[i].rectDame);
            //printf("color = 0, damesTab[%d].rectDame %d %d\n",i,damesTab[i].rectDame->x,damesTab[i].rectDame->y);
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
	//bar noir
	else if (i == 24)
	{
	    hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = 44;
            hitboxesTab[i].rectHB->h = height;
	}
	//bar blanc
	else if (i == 25)
	{
            hitboxesTab[i].rectHB->x = 490;
            hitboxesTab[i].rectHB->y = y1;
            hitboxesTab[i].rectHB->w = 44;
            hitboxesTab[i].rectHB->h = height;
	}
	//out blanc
	else if (i == 26)
	{
            hitboxesTab[i].rectHB->x = 1015;
            hitboxesTab[i].rectHB->y = y2;
            hitboxesTab[i].rectHB->w = width1;
            hitboxesTab[i].rectHB->h = height;
	}
	//out noir
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




void updateSGameState(SGameState* gamestate, SMove *moves,unsigned int *nbMoves, Player curPlayer){
 int i;

 for (i=0;i < *nbMoves;i++){
  //cas depuis un square vers un autre
  if ((moves[i].dest_point != 0 || moves[i].dest_point !=25) && (moves[i].src_point > 0 && moves[i].src_point < 25)){

    if (curPlayer == BLACK){

        if(gamestate->board[24-moves[i].dest_point].owner == BLACK || gamestate->board[24-moves[i].dest_point].owner == NOBODY) // si on mange un pion de l'adversaire ou on capture une nouvelle case
        {
            gamestate->board[24-moves[i].dest_point].nbDames += 1;

        }

        else if(gamestate->board[24-moves[i].dest_point].owner == WHITE) // si on mange un pion de l'adversaire ou on capture une nouvelle case
        {
            gamestate->bar[1] += 1; // on rajoute un pion dans la bar du blanc
        }

        gamestate->board[24-moves[i].src_point].nbDames -= 1;

        gamestate->board[24-moves[i].dest_point].owner = BLACK;

    }
    else if (curPlayer == WHITE){

        if(gamestate->board[moves[i].dest_point-1].owner == WHITE || gamestate->board[moves[i].dest_point-1].owner == NOBODY)
        {

            gamestate->board[moves[i].dest_point-1].nbDames += 1;

        }
        else if(gamestate->board[moves[i].dest_point-1].owner == BLACK) // si on mange un pion de l'adversaire ou on capture une nouvelle case
        {
            gamestate->bar[0] += 1; // on rajoute un pion dans la bar du noir
        }

        gamestate->board[moves[i].src_point-1].nbDames -= 1;
        gamestate->board[moves[i].dest_point-1].owner = WHITE;


    }
  }

  //cas depuis bar vers square
  else if (moves[i].src_point == 0 && (moves[i].dest_point < 25 && moves[i].dest_point > 0)){
   if (curPlayer == WHITE){

        if(gamestate->board[moves[i].dest_point-1].owner == WHITE || gamestate->board[moves[i].dest_point-1].owner == NOBODY) // si on mange un pion de l'adversaire ou on capture une nouvelle case
        {

            gamestate->board[moves[i].dest_point-1].nbDames += 1;

        }
        else if(gamestate->board[moves[i].dest_point-1].owner == BLACK)
        {
            gamestate->bar[0] += 1; // on rajoute un pion dans la bar du noir
        }

        gamestate->bar[1] -= 1;
        gamestate->board[moves[i].dest_point-1].owner = WHITE;

   }
   else if (curPlayer == BLACK){

        if(gamestate->board[24-moves[i].dest_point].owner == BLACK || gamestate->board[24-moves[i].dest_point].owner == NOBODY) // si on mange un pion de l'adversaire ou on capture une nouvelle case
        {

            gamestate->board[24-moves[i].dest_point].nbDames += 1;

        }
        else if(gamestate->board[24-moves[i].dest_point].owner == WHITE)
        {
            gamestate->bar[1] += 1; // on rajoute un pion dans la bar du blanc
        }

        gamestate->bar[0] -= 1;
        gamestate->board[24-moves[i].dest_point].owner = BLACK;
   }
  }
  //cas depuis square vers out
  else if (moves[i].dest_point == 25 && (moves[i].src_point < 25 && moves[i].src_point > 0)){
   if (curPlayer == WHITE){
        printf("gogole\n");
        gamestate->out[1] += 1;
        gamestate->board[moves[i].src_point-1].nbDames -= 1;
   }
   else if (curPlayer == BLACK){
        printf("gogole222\n");
        gamestate->out[0] += 1;
        gamestate->board[24-moves[i].src_point].nbDames -= 1;
   }
  }
 }

    for (i=0;i < 24;i++) // remettre à NOBODY les squares vides
    {
        if(gamestate->board[i].nbDames == 0) gamestate->board[i].owner = NOBODY;
        //printf("proprio magueule : i:%d %d\n", i,gamestate->board[i].owner);
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
        if(curPlayer == WHITE)
        {

            moves[*nbMoves].src_point = indiceHBTab[0];
            moves[*nbMoves].dest_point = indiceHBTab[1];
        }

        else if(curPlayer == BLACK)
        {

            if(indiceHBTab[0]!=0 && indiceHBTab[0]!=25)
            {
                moves[*nbMoves].src_point = 24-indiceHBTab[0]+1;printf("moncul\n");
            }
            else
            {
                moves[*nbMoves].src_point = indiceHBTab[0];
            }

            if(indiceHBTab[1]!=0 && indiceHBTab[1]!=25)
            {
                moves[*nbMoves].dest_point = 24-indiceHBTab[1]+1;
            }
            else
            {
                moves[*nbMoves].dest_point = indiceHBTab[1];
            }

        }

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
