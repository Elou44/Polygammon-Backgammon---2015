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
	unsigned int opponent;			// Couleur des pions adverses
	unsigned int scoreActuel[2];	// Nombre de manches gagnées, et celle de l'adversaire
	unsigned int scorePourGagner;	// Nombre de manches nécessaires pour gagner un match
	unsigned int scoreManche;		// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)
	unsigned int pions;				// Nombre de pions encore sur le plateau
	int mancheActuelle;				// Numéro de la manche jouée actuellement
	unsigned int resultatMatch;		// 1 si cette IA a gagnée, 0 sinon
}IA;


// Sinon on peut aussi regrouper cette structure avec IA
typedef struct {	// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)
	SMove mouvement;				// Numéros de cases accessibles en un mouvement
	int priorite;				// Numéros de cases accessibles en plusieurs mouvements
}Mouvements;

/*
typedef struct {
	int indice;						// Numéro de la case
	Square sq;						// Structure Square de la case
	Mouvements moves;				// Structure Mouvements de la case
}Carre;
*/

IA OliverJohn;

int verifPresence(int *tableau, int element, int taille)
{
	int i;
	
	for (i = 0; i < taille;i++)
	{
		if(tableau[i] == element)
		{
			return i;
		}
	}
	return -1;
}

int definePriority(int **AlliedSquares, int **EnnemySquares, SMove mov) {	// Définit le coefficient de priorité du mouvement décrit par le SMove donné en paramètre
	int i = 0;	// Indice de parcours de tableau
	int IndiceCaseDepart;	// Numéro de la case de départ en étude
	int IndiceCaseArrivee;	// Numéro de la case d'arrivée en étude
	
	// On cherche l'indice dans AlliedSquares de la case de départ
	for (i = 0; i < 15; i++)
	{
		if(AlliedSquares[0][i] == mov.src_point)
		{
			IndiceCaseDepart = i;
			break;
		}
	}
	
	// On cherche l'indice de la case d'arrivée
	if(verifPresence(AlliedSquares[1], mov.dest_point, 15) )	// Si la case d'arrivée est une case conquise
	{
		// On cherche l'indice parmis le tableau casesAllies
		for (i = 0; i < 15; i++)
		{
			if(AlliedSquares[0][i] == mov.dest_point)
			{
				IndiceCaseArrivee = i;
				break;
			}
		}
	}
	else
	{
		// Sinon on cherche l'indice parmis le tableau casesEnnemies
		for (i = 0; i < 15; i++)
		{
			if(EnnemySquares[0][i] == mov.dest_point)
			{
				IndiceCaseArrivee = i;
				break;
			}
		}
	}
	
	// Définition des priorités
	
	// PRIORITE 1 : mouvement d'un pion depuis notre bar
	if(mov.src_point == 0) { return 1; }	// Si le point de départ du mouvement est dans le bar (il a été mangé)
	
	// PRIORITE 2 : mouvement d'un pion isolé vers une case conquise
	if(AlliedSquares[1][IndiceCaseDepart] == 1)	// Si on a un pion tout seul sur une case et que la case d'arrivée est à nous
	{
		return 2;
	}
	
	// PRIORITE 3 : mouvement d'un pion pouvant manger un pion adverse
	if(EnnemySquares[1][IndiceCaseArrivee] == 1)	// Si on a un pion tout seul sur une case et que la case d'arrivée est à nous
	{
		return 3;
	}
	
	// PRIORITE 4 : mouvement d'un pion sur une case où on a un pion isolé
	if(AlliedSquares[1][IndiceCaseArrivee] == 1)
	{
		return 4;
	}
	
	// PRIORITE 5 : mouvement d'un pion vers le out
	if(mov.dest_point == 25 || mov.dest_point == 0)
	{
		return 5;
	}
	
	// PRIORITE 6 : mouvement par défaut
	return 6;
	
}


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

	
	OliverJohn.scoreActuel[0] = 0 ;
	OliverJohn.scoreActuel[1] = 0 ;
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
	OliverJohn.couleur = p;
	if(OliverJohn.couleur == 0) OliverJohn.opponent = 1;
	else OliverJohn.opponent = 0;
	OliverJohn.scoreManche = 0;
	OliverJohn.mancheActuelle++;
}

void EndGame()	// On indique juste que la manche est terminée, vu qu'on renvoie rien
/* Mais au final je sais pas si on doit afficher un truc, plutôt l'interface graphique
 pour qu'ils le fassent tout beau et tout, on verra pas la console sinon */
{
	printf("EndGame\n");
	printf("Manche terminée\n");
	printf("Score actuel : %s -> %du points\n", OliverJohn.nom, OliverJohn.scoreActuel[0]);
}

void EndMatch()	// On indique juste que le match est terminé
// Même chose ici, en fait je pense pas qu'on doive print un truc
// 
{
	printf("EndMatch\n");
	printf("Partie terminée\n");
	printf("IA %s avec un score de %du\n", OliverJohn.nom, OliverJohn.scoreActuel[0]);
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

	int casesAllies[2][15];			// Tableau des cases qui nous appartiennent
	int casesEnnemies[2][15];		// Tableau des cases ennemis
	Mouvements mouvts[60];			// Tableau des mouvements possibles
	int i, quatreMoves = 0;			// Indice de parcours de boucle, booléen indiquant si tirage de dés est un double
	int tirageDes[2];				// Copie du tirage de dés
	int j = 0, k = 0;				// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies

	printf("Début du tour\n");
	
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les résultats des dés pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}

	/*
	#############################################
	#Remplissage tableaux cases Alliées/Ennemies#
	#############################################
	*/

	// Parcours de chaque case du plateau pour repérer les cases à nous ou pas -> Remplissage des tableaux appartenance des cases
	if(gameState->bar[OliverJohn.couleur] > 0) {
		casesAllies[0][j] = 0;	// Sauvegarde n°case
		casesAllies[1][j] = gameState->bar[OliverJohn.couleur];	// On garde une structure Square donnant le nombre de Dames présentes sur la case 
		j++;
	}
	if(gameState->bar[OliverJohn.opponent] > 0) {
		casesEnnemies[0][k] = 0;	// Juste avant de garder la structure Square, on garde le numéro de la case (pour les mouvements)
		casesEnnemies[1][k] = gameState->bar[OliverJohn.opponent];	// On garde une structure Square donnant le nombre de Dames présentes sur la case 
		k++;
	}
	
	for (i = 0; i < len(gameState->board); i++)
	{
		if (gameState->board[i].owner == OliverJohn.couleur)	// Si le proprio de la case (enum Player) est égal à notre couleur
		{
			casesAllies[0][j] = i+1;	// Sauvegarde n°case
			casesAllies[1][j] = gameState->board[i].nbDames;	// On garde le nombre de pions sur la case
			j++;	// On incrémente l'indice de remplissage des cases alliées dès qu'on a remplit la case d'avant
		}
		else if(gameState->board[i].owner != -1)
		{
			casesEnnemies[0][k] = i+1;
			casesEnnemies[1][k] = gameState->board[i].nbDames;
			k++;	// On incrémente l'indice de remplissage des cases ennemies dès qu'on a remplit la case d'avant
		}
	}

	/*
	#############################################
	##### Listing des mouvements possibles ######
	#############################################
	*/

	// Boucle de remplissement de la structure casesAllies
	k = 0;
	for (j = 0; j < len(casesAllies); j++)	// Parmis toutes nos cases conquises
	{
		if(tirageDes[0] == tirageDes[1]) {	// Si le tirage des dés ets un double
			//On peut regarder directement si la case est occupé par au moins 2 ennemis
			quatreMoves = 1;	// Booléen à vrai
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
le premier dé n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				// On remplit l'objet SMove de la case
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;
				k++;
			}
			/* Si le premier directMove n'était pas possible, vu qu'on est dans le cas d'un tirage de double,
le deuxième mouvement est aussi impossible */
			
			if(!(gameState->board[j+2*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+2*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
deux dés n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+2*tirageDes[0]+1;
				k++;
			}
			
			if(!(gameState->board[j+3*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+3*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
trois dés n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+3*tirageDes[0]+1;
				k++;
			}
			
			
			if(!(gameState->board[j+4*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+4*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
quatre dés n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+4*tirageDes[0]+1;
				k++;
			}
			
			
		} else {
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
un dé n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;
				k++;
			}
			
			if(!(gameState->board[j+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[1]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
deux dés n'est pas à nous ET qu'il y a plus qu'un pions dessus */
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[1]+1;
				k++;
			}
			
			if(!(gameState->board[j+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]+tirageDes[1]].nbDames > 1)) {	/* Si la case
d'arrivée en utilisant deux dés n'est pas à nous ET qu'il y a plus qu'un pions dessus */

				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+tirageDes[1]+1;
				k++;
			}
		}
	}

	/*
	#############################################
	########## Choix des moves à faire ##########
	#############################################
	*/
	
	int nbdices = 0, nomove = 0;
	if(quatreMoves) {	// On attribue la valeur à nombre de dés selon le booléen indiquant un tirage double
		nbdices = 4;
	} else nbdices = 2;
	
	while(nbdices || nomove) {	// Tant qu'il nous reste des dés pour bouger OU qu'il n'y a plus e mouvements à faire
		nomove = 1;
		for(i = 0; i < len(casesAllies); i++)	// Parmis les cases conquises (i case de départ)
		{
			
		}
	}

}

/*
 - PRIORITE 1 : condition vérifier si on a des pions de sortis et qu'il faut sortir en priorité (TOP PRIORITE)
 - PRIORITE 2 : mouvement de pions tout seul sur leur case et qu'on peut sécuriser sur une pile    |  Par quart : de l'ennemi vers nous
 	-> si tous les pions adverses sont derriere, toujours securisés
 - PRIORITE 3 : mouvement de pions pouvant bouffer un adversaire (et pouvant être sécurisé après)  |  Resp. : de nous vers l'ennemi
 - PRIORITE 4 : création de case sécurisée
 - PRIORITE 5 : mouvement sécurisé
 - PRIORITE 6 : oups, sucks
 	-> prioriser les mouvements des pions qui ne sont pas dans le dernier quart
 - on trouve les pions -> parcours des cases
 	-> pions de chaques joueurs (case, nb)
 - on liste tous nos mouvements
 	-> mouvements possibles, passages
 - on essaie de les regrouper
 	-> regarder si deux mouvements arrivent sur la même case
 - on mange les pions de l'adversaire delon leur position
 	-> proche de notre côté, on mange toujours, du côté adverse, seulement si on peut sécuriser nos pions
 - si on ne peut faire que des "mauvais" moves, on fait celui qui induit le moins de risque
 	-> pas de pions ennemis devant, ou trop loin, ou proche de notre côté
 	
 comparer l'écart des dés et celui des cases de pions -> ils peuvent donc arriver sur la même case !
 comparer les cases d'arrivées et les cases des pions adverses -> les éliminer ou trouver des cases où manger l'adversaire
 comparer les cases d'arrivées et les cases des pions possédés -> faire des mouvements "safe"
 comparer les mouvements restants par rapport aux positions adverses
 Trouver les cases où on a qu'un seul pion, et essayer de les envoyer vers des cases déjà possédés ou les faire rejoindre par un autre pion
*/
