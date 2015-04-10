#include "backgammon.h"
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////
// Dans la librairie
//

// Structure d'une IA, regroupant les infos dont on a besoin pour les fonctions et la stratégie
typedef struct {
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

// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)
typedef struct {
	SMove mouvement;				// Numéros de cases accessibles en un mouvement
	int priorite;					// Numéros de cases accessibles en plusieurs mouvements
}Mouvements;

// Déclaration de l'IA
IA OliverJohn;


void InitLibrary(char name[50])
{
	printf("Initiating library...\n");
	strcpy(name, "OliverJohn");
}

void StartMatch(const unsigned int target_score)
{
	printf("Starting match...\n");
	/* En paramètres le nombre de Game à gagner pour remporter le match
	Initialiser l'IA pour un match
	Initialisation du nombre de manches à gagner dans la structure
	Initialisation à 0 du nombre de manches actuelles gagnées
	*/

	
	OliverJohn.scoreActuel[0] = 0;
	OliverJohn.scoreActuel[1] = 0;
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
	printf("Score actuel : %s -> %d points\n", OliverJohn.nom, OliverJohn.scoreActuel[0]);
	
}

void EndMatch()	// On indique juste que le match est terminé
// Même chose ici, en fait je pense pas qu'on doive print un truc
// 
{
	printf("EndMatch\n");
	printf("Partie terminée\n");
	printf("IA %s avec un score de %d\n", OliverJohn.nom, OliverJohn.scoreActuel[0]);
}

int DoubleStack(const SGameState * const gameState)
{
	printf("DoubleStack\n");
	return(0);
}

int TakeDouble(const SGameState * const gameState)
{
	// Retourne 1 si on prend, retourne 0 sinon
	printf("TakeDouble\n");
	
	return(0);
}


// IA DE TEST

int definePriority(const SGameState * const gameState, SMove mov)
{
	printf("### Dans definePriority de %d | %d dames vers %d | %d dames \n", mov.src_point, gameState->board[mov.src_point].nbDames, mov.dest_point, gameState->board[mov.dest_point].nbDames);
	
	// PRIORITE 1 : mouvement d'un pion depuis notre bar
	if(mov.src_point == -1)
	{
		printf("1 - Sortir pion du bar\n");
		return 1;
	}
	
	// PRIORITE 2 : mouvement d'un pion isolé vers une case conquise
	if(gameState->board[mov.src_point].nbDames == 1 && gameState->board[mov.dest_point].owner == OliverJohn.couleur)
	{
		printf("2 - Pion isolé vers case conquise\n");
		return 2;
	}

	// PRIORITE 3 : mouvement d'un pion sécurisé vers une case sécurisée
	if(gameState->board[mov.src_point].nbDames > 2 && gameState->board[mov.dest_point].nbDames > 2 && gameState->board[mov.dest_point].owner == OliverJohn.couleur)
	{
		printf("3 - Pion sécurisé vers case conquise\n");
		return 3;
	}
				
	// PRIORITE 4 : mouvement d'un pion non sécurisé pour manger un pion adverse
	if(gameState->board[mov.src_point].nbDames == 1 && gameState->board[mov.dest_point].owner != OliverJohn.couleur && gameState->board[mov.dest_point].nbDames == 1)
	{
		printf("4 - Pion non sécurisé mangeant un pion\n");
		return 4;
	}
		
	// PRIORITE 5 : mouvement d'un pion sécurisé pour manger un adversaire
	if(gameState->board[mov.src_point].nbDames > 1 && gameState->board[mov.dest_point].owner != OliverJohn.couleur && gameState->board[mov.dest_point].nbDames == 1)
	{
		printf("5 - Pion sécurisé mangeant un pion\n");
		return 5;
	}
		
	// PRIORITE 6 : mouvement d'un pion vers le out
	if(mov.dest_point >= 25 || mov.dest_point < 0)
	{
		printf("6 - Sortie de pion\n");
		return 6;
	}
	
	// PRIORITE 7 : mouvement par défaut
	printf("7 - Défault\n");
	return 7;
}


void PlayTest(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
	Mouvements mouvts[60];			// Liste des mouvements possibles
	Mouvements tempMoves[60];		// Liste temporaire des mouvements à effectuer, classés par ordre de priorité
	SGameState copieGameState;		// Copie de la structure gameState
	copieGameState = *gameState;
	int i, quatreMoves = 0;			// Indice de parcours de boucle, booléen indiquant si le tirage de dés est un double
	int tirageDes[2];				// Copie du tirage de dés
	int nbDes = 2, nbDices;			// Variables indiquant le nombre de dés pouvant être utilisé par tour
	int prio = 1;					// Variable indiquant la priorité en cours d'étude
	int distance;					// VAriable indiquant l'écart entre 2 cases du plateau
	int indiceDernierPion;			// Variable donnant l'indice du pion le plus éloigné du out
	int nbPions;					// Variable donnant le nombre de pions restant sur une case
	int indiceTempMoves;			// Indice du mouvement de tempMoves à remplacer
	int caseEnEtude = -1;			// Numéro de la dernière case étudiée
	int j = 0, k = 0, l = 0;		// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies, indice remplissage tableau moves
	int m = 0;						// Variable servant à indiquer le nombre de dés utilisés pour un seul mouvement
	int n = 0;						// Indice de remplissage du tableau tempMoves

	static int nbTour = 1;

	printf("Tour %d : Début du tour IA de test. On est les %d et les des sont : %d/%d\n",nbTour, OliverJohn.couleur, dices[0], dices[1]);
	nbTour++;
	
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les résultats des dés pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}

	if(dices[0] == dices[1])
	{
		quatreMoves = 1;	// Si le tirage est un double, alors le booléen quatreMoves prend 1
		nbDes = 4;			// Tirage double donc 4 dés utilisables
	}

	nbDices = nbDes;


	/*
	##########################################################
	################### Listing Mouvements ###################
	##########################################################
	*/

	// Listing mouvements à faire depuis le bar si il y en a
	// Attribution des mouvements depuis le bar
	printf("Videau : %d pions\n", gameState->bar[OliverJohn.couleur]);
	if(gameState->bar[OliverJohn.couleur] > 0)
	{
		for(i = 0; i < gameState->bar[OliverJohn.couleur]; i++)		// Parmis les pions dans notre bar
		{
			if(quatreMoves != 1)	// Si le tirage n'est pas un double
			{
				// EN UTILISANT 1 DE
				for(m = 0; m < 2; m++)	// Boucle pour prendre en compte les deux dés séparément (d'abord en utilisant le premier puis le deuxième)
				{
					printf("BAR : m : %d pion : %d, avec %d\n", m, i, i-tirageDes[m]);
					// Si la case d'arrivée est à moi OU neutre alors mouvement possible
					if(gameState->board[24+tirageDes[m]].owner == OliverJohn.couleur || gameState->board[24+tirageDes[m]].owner == -1)
					{
						//printf("1 - La cellule %d semble m'appartenir\n", i);
						//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = 24+tirageDes[m];						// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

						printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
					// Si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
					else if((gameState->board[24+tirageDes[m]].owner != OliverJohn.couleur && gameState->board[24+tirageDes[m]].nbDames == 1)  || gameState->board[24+tirageDes[m]].owner == -1)
					{
						//printf("2 - La cellule %d semble m'appartenir\n", i);
						//printf("2 - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = 24+tirageDes[m];						// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

						printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
				}
				// EN UTILISANT 2 DES
				// Si la case d'arrivée est à moi OU neutre alors mouvement possible
				if(gameState->board[24+tirageDes[0]+tirageDes[1]].owner == OliverJohn.couleur || gameState->board[24+tirageDes[0]+tirageDes[1]].owner == -1)
				{
					//printf("1 - La cellule %d semble m'appartenir\n", i);
					//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = 24+tirageDes[0]+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

					printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					
					k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
				// Si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
				else if((gameState->board[24+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[24+tirageDes[0]+tirageDes[1]].nbDames == 1)  || gameState->board[24+tirageDes[0]+tirageDes[1]].owner == -1)
				{
					//printf("2 - La cellule %d semble m'appartenir\n", i);
					//printf("2 - La cellule %d non par contre\n",
					//i+tirageDes[0]);
					mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = 24+tirageDes[0]+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

					printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
			}
			else
			{
				for(m = 1; m < 5; m++)	// Boucle pour prendre en compte les trois utilisations possibles des dés (en utilisant 1 dé, 2 dés, puis 3 dés puis 4 dés)
				{
					// SOIT la case d'arrivée m'appartient SOIT elle est neutre
					if(gameState->board[24+m*tirageDes[0]].owner == OliverJohn.couleur  || gameState->board[24+m*tirageDes[0]].owner == -1)
					{
						//printf("5 - La cellule %d semble m'appartenir\n", i);
						//printf("5 - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = 24+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
						
						printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
					// SOIT la case d'arrivée ne m'appartient pas ET il n'y a qu'un pion ennemi dessus OU elle est neutre
					else if((gameState->board[24+m*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[24+m*tirageDes[0]].nbDames == 1) || gameState->board[24+m*tirageDes[0]].owner == -1)
					{
						//printf("5' - La cellule %d semble m'appartenir\n", i);
						//printf("5' - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = 24+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement						
						
						printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
				}
			}
		}
	}



	// Listing pour tous nos pions du plateau
	for(i = 0; i < 24; i++)	// Parmis les cases du plateau
	{
		printf("///// Je travaille sur la cellule %d, appartenant à %d\n", i, gameState->board[i].owner);
		if(quatreMoves != 1)	// Si le tirage n'est pas un double
		{
			// EN UTILISANT 1 DE
			// Si la case de départ est à moi ET que la case d'arrivée est à moi alors mouvement possible
			if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+tirageDes[0]].owner == OliverJohn.couleur || gameState->board[i+tirageDes[0]].owner == -1) || (i+tirageDes[0] < 0)))
			{
				//printf("1 - La cellule %d semble m'appartenir\n", i);
				//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}
			// Si la case de départ est à moi ET que la case d'arrivée n'est pas à moi MAIS qu'il a un seul pion dessus alors mouvement possible
			else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[i+tirageDes[0]].nbDames == 1)  || gameState->board[i+tirageDes[0]].owner == -1 || (i+tirageDes[0] < 0)))
			{
				//printf("2 - La cellule %d semble m'appartenir\n", i);
				//printf("2 - La cellule %d non par contre\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}

			// Si la case de départ est à moi ET que la case d'arrivée est à moi alors mouvement possible
			if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+tirageDes[1]].owner == OliverJohn.couleur || gameState->board[i+tirageDes[1]].owner == -1) || (i+tirageDes[1] < 0)))
			{
				//printf("1 - La cellule %d semble m'appartenir\n", i);
				//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}
			// Si la case de départ est à moi ET que la case d'arrivée n'est pas à moi MAIS qu'il a un seul pion dessus alors mouvement possible
			else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[i+tirageDes[1]].nbDames == 1)  || gameState->board[i+tirageDes[1]].owner == -1 || (i+tirageDes[1] < 0)))
			{
				//printf("2 - La cellule %d semble m'appartenir\n", i);
				//printf("2 - La cellule %d non par contre\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}

			// EN UTILISANT 2 DES
			// Si la case d'arrivée est à moi OU neutre alors mouvement possible
			if(gameState->board[i].owner == OliverJohn.couleur && (gameState->board[i+tirageDes[0]+tirageDes[1]].owner == OliverJohn.couleur || gameState->board[i+tirageDes[0]+tirageDes[1]].owner == -1 || (i+tirageDes[0]+tirageDes[1] < 0)))
			{
				//printf("1 - La cellule %d semble m'appartenir\n", i);
				//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[0]+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Double mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}
			// Si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
			else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[i+tirageDes[0]+tirageDes[1]].nbDames == 1)  || gameState->board[i+tirageDes[0]+tirageDes[1]].owner == -1 || (i+tirageDes[0]+tirageDes[1] < 0)))
			{
				//printf("2 - La cellule %d semble m'appartenir\n", i);
				//printf("2 - La cellule %d non par contre\n", i+tirageDes[0]);
				mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
				mouvts[k].mouvement.dest_point = i+tirageDes[0]+tirageDes[1];						// Sauvegarde du numéro de la case d'arrivée
				mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
				printf("Double mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}
		}
		else
		{
			for(m = 1; m < 5; m++)	// Boucle pour prendre en compte les trois utilisations possibles des dés (en utilisant 1 dé, 2 dés, puis 3 dés puis 4 dés)
			{
				printf("m : %d, case : %d, dest : %d\n", m, i, i+m*tirageDes[0]);
				// Si la case de départ m'appartient ET SOIT la case d'arrivée m'appartient SOIT elle est neutre
				if(gameState->board[i].owner == OliverJohn.couleur && ( gameState->board[i+m*tirageDes[0]].owner == OliverJohn.couleur  || gameState->board[i+m*tirageDes[0]].owner == -1 || (i+m*tirageDes[0] < 0)))
				{
					//printf("5 - La cellule %d semble m'appartenir\n", i);
					//printf("5 - La cellule %d non par contre\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = i+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
					printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
					k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
				else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+m*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[i+m*tirageDes[0]].nbDames == 1) || gameState->board[i+m*tirageDes[0]].owner == -1 || (i+m*tirageDes[0] < 0)))
				{
					//printf("5' - La cellule %d semble m'appartenir\n", i);
					//printf("5' - La cellule %d non par contre\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = i+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
					printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
					k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
			}
		}
	}
	

	/*
	##########################################################
	#################### Choix Mouvements ####################
	##########################################################
	*/
	
	while(prio < 8)
	{
		printf("## Verif les prio %d\n", prio);
		for(i = 0; i < k; i++)	// Parmis les mouvements de mouvts (indice k non remis à zéro donc on a la taille réel des infos de mouvts)
		{
			printf("Je travaille sur %d à %d de prio %d\n", mouvts[i].mouvement.src_point, mouvts[i].mouvement.dest_point, mouvts[i].priorite);

			if(mouvts[i].priorite == prio)
			{
				nbPions = copieGameState.board[mouvts[i].mouvement.src_point].nbDames;	// Sauvegarde du nombre de pions sur la case de départ en étude

				if(mouvts[i].mouvement.dest_point < 0)
				{
					printf("# Calcul distance dest < 0\n");
					distance = -mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point;
				}
				else
				{
					printf("# Distance sinon...");
					distance = mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point;
				}

				if(mouvts[i].mouvement.src_point == -1)
				{
					distance = mouvts[i].mouvement.dest_point - 24;
					nbPions = copieGameState.bar[OliverJohn.couleur];
					printf("# Distance videau ! avec %d pions\n", nbPions);
				}

				/*
				// Parmis les mouvement stockés dans tempMoves
				for(j = 0; j < n; j++)
				{
					// Si le mouvement tempMoves n'utilise qu'un seul dé ET que la priorité du mouvement n'est pas 1
					if((tempMoves[j].mouvement.dest_point - tempMoves[j].mouvement.src_point == -dices[0] || tempMoves[j].mouvement.dest_point - tempMoves[j].mouvement.src_point == -dices[1]) && tempMoves[j].priorite = 1)
					{
						// Si la distance du mouvement en étude utilise 2 ou 3 ou 4 dés
						if((distance == tirageDes[0]+tirageDes[1]) || (distance == 3*tirageDes[0]) || (distance == 4*tirageDes[0]))
						{
							printf("J'ai décrémenté pour %d à %d\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point);
							indiceTempMoves = j;													// Affectation de l'indice du mouvement tempMoves n'utilisant qu'un seul dé pour le remplacer par un mouvement utilisant plus de dés
							nbDes++;																// Incrémentation du dé que l'on récupère en remplaçant ce mouvement
							copieGameState.board[tempMoves[j].mouvement.src_point].nbDames--;		// Incrémentation du nombre de pions sur la case du mouvement en étude
						}
					}
				}
				*/

				printf("\tJe rentre dans le if avec %d des et ecart : %d et %d pions et pion le plus loin est %d\n", nbDes, distance, nbPions, indiceDernierPion);

				// Mouvement utilisant 1 seul dé
				// Si le nombre de mouvemnts dans tempMoves ET qu'il me reste encore 1 dé à utiliser ET la distance est bien égale à la valeur d'un dé ET qu'il y a encore des pions sur la case
				if((n < 5 && nbDes >= 1 && (distance == tirageDes[0] || distance == tirageDes[1]) && nbPions > 0) && (tirageDes[0] != -100 || tirageDes[1] != -100))
				{
					// Si la case d'arrivée du mouvement est plus grande que 24 OU bien plus petite que 0
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						// Si le pion le plus éloigné du out se situe dans le dernier Jan
						if(indiceDernierPion < 6)
						{
							printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
							tempMoves[n].mouvement.dest_point = 25;
							tempMoves[n].priorite = mouvts[i].priorite;
							printf("\t\t1 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes--;
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;

							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;
							}

							if(distance == tirageDes[0] && quatreMoves == 0)
							{
								tirageDes[0] = -100;
							}
							else if(distance == tirageDes[1] && quatreMoves == 0)
							{
								tirageDes[1] = -100;
							}

							n++;
							printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					else
					{
						printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;
						tempMoves[n].priorite = mouvts[i].priorite;
						printf("\t\t1 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes--;
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;

						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;
						}

						if(distance == tirageDes[0] && quatreMoves == 0)
						{
							tirageDes[0] = -100;
						}
						else if(distance == tirageDes[1] && quatreMoves == 0)
						{
							tirageDes[1] = -100;
						}

						n++;
						printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
				// Mouvement utilsant 2 dés
				// Si
				else if((n < 5 && nbDes >= 2 && (distance == tirageDes[0]+tirageDes[1]) && nbPions > 0) && (tirageDes[0] != -100 && tirageDes[1] != -100))
				{
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
							tempMoves[n].mouvement.dest_point = 25;
							tempMoves[n].priorite = mouvts[i].priorite;
							printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=2;
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;

							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;
							}

							if(quatreMoves == 0)
							{
								tirageDes[1] = -100;
								tirageDes[0] = -100;
							}

							n++;
							printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					else
					{
						printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;
						tempMoves[n].priorite = mouvts[i].priorite;
						printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=2;
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;

						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;
						}

						if(quatreMoves == 0)
						{
							tirageDes[1] = -100;
							tirageDes[0] = -100;
						}

						n++;
						printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
				else if(n < 5 && nbDes >= 3 && (distance == 3*tirageDes[0]) && nbPions > 0)
				{
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
							tempMoves[n].mouvement.dest_point = 25;
							tempMoves[n].priorite = mouvts[i].priorite;
							printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=3;
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;
							}
							n++;
							printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					else
					{
						printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;
						tempMoves[n].priorite = mouvts[i].priorite;
						printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=3;
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;
						}
						n++;
						printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
					
				}
				else if(n < 5 && nbDes >= 4 && (distance == 4*tirageDes[0]) && nbPions > 0)
				{
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
							tempMoves[n].mouvement.dest_point = 25;
							tempMoves[n].priorite = mouvts[i].priorite;
							printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=4;
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;
							}
							n++;
							printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					else
					{
						printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;
						tempMoves[n].priorite = mouvts[i].priorite;
						printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=4;
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;
						}
						n++;
						printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
			}
		}
		prio++;
	}

	if(nbDes > 0)
	{
		printf("JE NE PEUX PAS BOUGER !\n");
		return;
	}

	for(i = 0; i < n; i++)
	{
		moves[i].src_point = tempMoves[i].mouvement.src_point;
		moves[i].dest_point = tempMoves[i].mouvement.dest_point;
		*nbMove = n;
		printf("Je me déplace de %d à %d avec %d moves\n", moves[i].src_point, moves[i].dest_point, *nbMove);
	}

	printf("Des : %d / %d --- ", dices[0], dices[1]);
	printf("Tour IA de test terminé Bouyah ! A toi de jouer.\n");
}

// Maintenant il faut favoriser les mouvements utilisant 2 dés plutôt que 1 dé