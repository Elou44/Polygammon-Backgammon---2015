#include "backgammon.h"
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////
// Dans la librairie
//

// Apparemment il faut faire une structure globale pour stocker toutes les infos dont on a besoin pour implémenter nos fonctions

typedef struct {	// Structure d'une IA, regroupant les infos dont on a besoin pour les fonctions et la stratégie
	char nom[50];					// Nom de l'IA
	unsigned int couleur;			// Couleur des pions de l'IA
	unsigned int scoreActuel[2];	// Nombre de manches gagnées
	unsigned int scorePourGagner;	// Nombre de manches nécessaires pour gagner un match
	unsigned int scoreManche;		// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)
	unsigned int pions;				// Nombre de pions encore sur le plateau
	int mancheActuelle;				// Numéro de la manche jouée actuellement
	unsigned int resultatMatch;		// 1 si cette IA a gagnée, 0 sinon
} IA;

// Sinon on peut aussi regrouper cette structure avec IA
typedef struct {	// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)
	int directMove[2];				// Numéros de cases accessibles en un mouvement
	int longMove[3];				// Numéros de cases accessibles en plusieurs mouvements
}Mouvements;

typedef struct {
	int indice;						// Numéro de la case
	Square sq;						// Structure Square de la case
	Mouvements moves;				// Structure Mouvements de la case
}Carre;

IA OliverJohn;

void InitLibrary(char name[50])
{
	printf("Initiating library...\n");
	strcopy();
}

void StartMatch(const unsigned int target_score)
{
	printf("Starting match...\n");
	/* En paramètres le nombre de Game à gagner pour remporter le match
	Initialiser l'IA pour un match
	Initialisation du nombre de manches à gagner dans la structure
	Initialisation à 0 du nombre de manches actuelles gagnées
	*/

	OliverJohn.scoreActuel = 0;
	OliverJohn.scorePourGagner = target_score;
	OliverJohn.mancheActuelle = -1;
	OliverJohn.resultatMatch = 0;
}

void StartGame(Player p)
{
	printf("StartGame\n");
	/* En paramètre l'énumération Player disant à qui appartient la case
	Initialiser l'IA pour une manche
	Initialisation du score de la manche à 0
	*/

	OliverJohn.scoreManche = 0;
	OliverJohn.mancheActuelle++;
}

void EndGame()	// On indique juste que la manche est terminée, vu qu'on renvoie rien
/* Mais au final je sais pas si on doit afficher un truc, plutôt l'interface graphique
 pour qu'ils le fassent tout beau et tout, on verra pas la console sinon */
{
	printf("EndGame\n");
	printf("Manche terminée\n");
	printf("Score actuel : %s -> %d points\n", OliverJohn.nom, OliverJohn.scoreActuel);
}

void EndMatch()	// On indique juste que le match est terminé
// Même chose ici, en fait je pense pas qu'on doive print un truc
// 
{
	printf("EndMatch\n");
	printf("Partie terminée\n");
	printf("IA %s avec un score de %d\n", OliverJohn.nom, OliverJohn.scoreActuel);
}

int DoubleStack(const SGameState * const gameState)
{
	printf("DoubleStack\n");
	return(0);
}

int TakeDouble(const SGameState * const gameState)
{
	printf("TakeDouble\n");
	return(0);
}

void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{

	/*
	#############################################
	######### Déclaration des variables #########
	#############################################
	*/

	/* Ces tableaux sont Static car on les remplit une fois et on veut pas qu'ils se vident
à chaque appel de PlayTurn() */
	// Ou alors on ajoute ces tableaux à notre structure IA...
	Carre casesAllies[15];		// Tableau des pions qui nous appartiennent
	Carre casesEnnemies[15];		// Tableau des pions ennemis
	int i;							// Indice de parcours de boucle
	int j = 0, k = 0;				// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies

	printf("PlayTurn\n");

	/*
	#############################################
	#Remplissage tableaux cases Alliées/Ennemies#
	#############################################
	*/

	// Parcours de chaque case du plateau pour repérer les cases à nous ou pas -> Remplissage des tableaux appartenance des cases
	for (i = 0; i < len(gameState.board); i++)
	{
		if (gameState.board[i].owner == OliverJohn.couleur)	// Si le proprio de la case (enum Player) est égal à notre couleur
		{
			casesAllies[j].indice = i;	// Juste avant de garder la structure Square, on garde le numéro de la case (pour les mouvements)
			casesAllies[j].sq = gameState.board[i];	// On garde une structure Square donnant le nombre de Dames présentes sur la case 
			j++;	// On incrémente l'indice de remplissage des cases alliées dès qu'on a remplit la case d'avant
		}
		else
		{
			casesEnnemies[k].indice = i;
			casesEnnemies[k].sq = gameState.board[i];
			k++;	// On incrémente l'indice de remplissage des cases ennemies dès qu'on a remplit la case d'avant
		}
	}

	/*
	#############################################
	##### Listing des mouvements possibles ######
	#############################################
	*/

	/* Il nous faudrait soit, un tableau pour stocker la case d'où on bouge les pions et les numéros des cases où on peut aller
c'est à dire 3 mouvements max pour un pion, où créer une structure Mouvements, avec la case d'où on part et les cases possibles */
	for (j = 0; j < len(casesAllies); j++)
	{
		if(dices[0] == dices[1]) {
			//On peut regarder directement si la case est occupé par au moins 2 ennemis
			casesAllies[j]->moves->directMove[0] = j+dices[0];
			casesAllies[j]->moves->directMove[1] = -1;
			casesAllies[j]->moves->longMove[0] = j+2*dices[0];
			casesAllies[j]->moves->longMove[1] = j+3*dices[0];
			casesAllies[j]->moves->longMove[2] = j+4*dices[0];
		} else {
			casesAllies[j]->moves->directMove[0] = j+dices[0];
			casesAllies[j]->moves->directMove[1] = j+dices[1];
			casesAllies[j]->moves->longMove[0] = j+dices[0]+dices[1];
			casesAllies[j]->moves->longMove[1] = -1;
			casesAllies[j]->moves->longMove[2] = -1;
		}
	}

	/*
	#############################################
	########## Choix des moves à faire ##########
	#############################################
	*/


}

/*
 - on trouve les pions -> parcours des cases
 	-> pions de chaques joueurs (case, nb)
 - on liste tous nos mouvements
 	-> mouvements possibles, passages
 - on essaie de les regrouper
*/