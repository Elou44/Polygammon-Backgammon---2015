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
	unsigned int scoreActuel;		// Nombre de manches gagnées
	unsigned int scorePourGagner;	// Nombre de manches nécessaires pour gagner un match
	unsigned int scoreManche;		// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)
	unsigned int pions;				// Nombre de pions encore sur le plateau
	int mancheActuelle;				// Numéro de la manche jouée actuellement
	unsigned int resultatMatch;		// 1 si cette IA a gagnée, 0 sinon
} IA;

typedef struct {	// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)
	int caseDepart;					// Numéro de la case de départ
	int petitMove;					// Numéro de la case la plus proche où l'on pourrait aller avec un dé
	int grandMove;					// Numéro de la case la plus éloignée où l'on pourrait aller avec un dé
	int totalMove;					// Numéro de la case où l'on pourrait aller avec deux dés
}Mouvements;

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
	static int casesAllies[];		// Tableau des pions qui nous appartiennent
	static int casesEnnemies[];		// Tableau des pions ennemis
	int mouvements[];				// /!\ A VOIR SI ON GARDE CA OU UNE STRUCTURE /!\
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
			casesAllies[j] = i;	// Juste avant de garder la structure Square, on garde le numéro de la case (pour les mouvements)
			j++;
			casesAllies[j] = gameState.board[i];	// On garde une structure Square donnant le nombre de Dames présentes sur la case
			j++;	// On incrémente l'indice de remplissage des cases alliées dès qu'on a remplit la case d'avant
		}
		else
		{
			casesEnnemies[k] = i;
			k++;
			casesEnnemies[k] = gameState.board[i];
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
		casesAllies[j]
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