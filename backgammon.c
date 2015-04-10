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
	unsigned int scoreManche;		// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)
	int mancheActuelle;				// Numéro de la manche jouée actuellement
}IA;

// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)
typedef struct {
	SMove mouvement;				// Numéros de cases accessibles en un mouvement
	int priorite;					// Numéros de cases accessibles en plusieurs mouvements
}Mouvements;

// Déclaration de l'IA
IA OliverJohn;


// Fonction initiant le nom de la librairie
void InitLibrary(char name[50])
{
	strcpy(name, "OliverJohn");								// Attribution du nom de l'IA dans name
}

// Fonction  initialisant la structure IA pour un début de match
void StartMatch(const unsigned int target_score)
{
	OliverJohn.mancheActuelle = -1;							// Définition de la manche actuelle à -1, car on incrémente directement en début de manche
}

// Fonction initialisant la structure IA pour un début de manche
void StartGame(Player p)
{
	//printf("StartGame\n");
	OliverJohn.couleur = p;									// Attribution de la couleur de l'IA
	if(OliverJohn.couleur == 0) OliverJohn.opponent = 1;	// Attribution de la couleur du joueur adverse
	else OliverJohn.opponent = 0;
	OliverJohn.scoreManche = 0;								// Attribution du score de la manche en cours (somme des indices des cases possédées)
	OliverJohn.mancheActuelle++;							// Incrémentation du numéro de la manche
}

// Fonction mettant à jour la structure IA pour une fin de game
void EndGame()
{
	OliverJohn.scoreManche = 0;								// Attribution du score de la manche en cours (somme des indices des cases possédées)
	OliverJohn.couleur = -1;								// Attribution de la couleur neutre pour l'IA
	OliverJohn.opponent = -1;								// Attribution de la couleur neutre pour l'adversaire
}

// Fonction mettant à jour la structure IA pour une fin de match
void EndMatch()
{

}

// Fonction calculant le score de l'adversaire pour la manche actuelle
int calculScoreEnnemi(const SGameState * const gameState)
{
	int i;													// Variable de parcours du board
	int scoreEnnemi = 0;									// Score de la manche actuelle de notre IA

	// Parmis les cases du board
	for(i = 1; i < 25; i++)
	{
		// Si la case appartient à l'ennemi, calcul de son score
		if(gameState->board[i].owner != OliverJohn.couleur)
		{
			scoreEnnemi = scoreEnnemi + i*gameState->board[i].nbDames;		// Ajout du scoreEnnemi précédent plus l'indice de la case en cours multiplié par le nombre de pions présents sur la case
		}
	}
	return scoreEnnemi;
}

// Fonction calculant le score de l'IA pour la manche actuelle
int calculScoreIA(const SGameState * const gameState)
{
	int i;													// Variable de parcours du board
	int scoreIA = 0;										// Score de la manche actuelle de notre IA

	// Parmis les cases du board
	for(i = 1; i < 25; i++)
	{
		// Si la case appartient à notre IA, calcul de son score
		if(gameState->board[i].owner == OliverJohn.couleur)
		{
			scoreIA = scoreIA + i*gameState->board[i].nbDames;				// Ajout du scoreIA précédent plus l'indice de la case en cours multiplié par le nombre de pions présents sur la case
		}
	}
	return scoreIA;
}

// Fonction proposant au joueur adverse de prendre un double ou non
int DoubleStack(const SGameState * const gameState)
{
	// Si le score de l'IA est supérieur au score de l'adversaire
	if((OliverJohn.scoreManche = calculScoreIA(gameState)) >= 100 +  calculScoreEnnemi(gameState))
	{
		return 1;	// Je demande un double
	}
	else
	{
		return 0;	// Je ne propose pas de double
	}
}

// Fonction décidant la prise d'un double proposé par l'adversaire
int TakeDouble(const SGameState * const gameState)
{
	// Si le score de l'IA est supérieur au score de l'adversaire
	if((OliverJohn.scoreManche = calculScoreIA(gameState)) >= calculScoreEnnemi(gameState))
	{
		return 1;	// J'accepte le double
	}
	else
	{
		return(0);	// Je décline le double
	}
}



// Fonction calculant le coefficient de priorité selon la position des pions ennemis et la position des pions alliés
int definePriority(const SGameState * const gameState, SMove mov)
{
	//printf("### Dans definePriority de %d | %d dames vers %d | %d dames \n", mov.src_point, gameState->board[mov.src_point].nbDames, mov.dest_point, gameState->board[mov.dest_point].nbDames);
	
	// PRIORITE 1 : mouvement d'un pion depuis notre bar
	if(mov.src_point == -1)
	{
		//printf("1 - Sortir pion du bar\n");
		return 1;
	}
	
	// PRIORITE 2 : mouvement d'un pion isolé vers une case conquise
	if(gameState->board[mov.src_point].nbDames == 1 && gameState->board[mov.dest_point].owner == OliverJohn.couleur)
	{
		//printf("2 - Pion isolé vers case conquise\n");
		return 2;
	}

	// PRIORITE 3 : mouvement d'un pion sécurisé vers une case sécurisée
	if(gameState->board[mov.src_point].nbDames > 2 && gameState->board[mov.dest_point].nbDames > 2 && gameState->board[mov.dest_point].owner == OliverJohn.couleur)
	{
		//printf("3 - Pion sécurisé vers case conquise\n");
		return 3;
	}
				
	// PRIORITE 4 : mouvement d'un pion non sécurisé pour manger un pion adverse
	if(gameState->board[mov.src_point].nbDames == 1 && gameState->board[mov.dest_point].owner != OliverJohn.couleur && gameState->board[mov.dest_point].nbDames == 1)
	{
		//printf("4 - Pion non sécurisé mangeant un pion\n");
		return 4;
	}
		
	// PRIORITE 5 : mouvement d'un pion sécurisé pour manger un adversaire
	if(gameState->board[mov.src_point].nbDames > 1 && gameState->board[mov.dest_point].owner != OliverJohn.couleur && gameState->board[mov.dest_point].nbDames == 1)
	{
		//printf("5 - Pion sécurisé mangeant un pion\n");
		return 5;
	}
		
	// PRIORITE 6 : mouvement d'un pion vers le out
	if(mov.dest_point >= 25 || mov.dest_point < 0)
	{
		//printf("6 - Sortie de pion\n");
		return 6;
	}
	
	// PRIORITE 7 : mouvement par défaut
	//printf("7 - Défault\n");
	return 7;
}




// Fonction du déroulement de l'IA
void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
	/*
	##########################################################
	################## Déclaration variables #################
	##########################################################
	*/

	Mouvements mouvts[60];			// Liste des mouvements possibles
	Mouvements tempMoves[60];		// Liste temporaire des mouvements à effectuer, classés par ordre de priorité
	SGameState copieGameState;		// Copie de la structure gameState
	copieGameState = *gameState;
	int i, quatreMoves = 0;			// Indice de parcours de boucle, booléen indiquant si le tirage de dés est un double
	int tirageDes[2];				// Copie du tirage de dés
	int nbDes = 2, nbDices;			// Variables indiquant le nombre de dés pouvant être utilisé par tour (une copie pouvant être modifiée)
	int prio = 1;					// Variable indiquant la priorité en cours d'étude
	int distance;					// VAriable indiquant l'écart entre 2 cases du plateau
	int ajustement = -1;			// Variable d'ajustement pour si on contrôle les pions noirs ou les pions blancs (utile pour les calculs de distance notamment)
	int indiceDernierPion;			// Variable donnant l'indice du pion le plus éloigné du out
	int nbPions;					// Variable donnant le nombre de pions restant sur une case
	int indiceTempMoves;			// Indice du mouvement de tempMoves à remplacer
	int caseEnEtude = -1;			// Numéro de la dernière case étudiée
	int j = 0, k = 0, l = 0;		// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies, indice remplissage tableau moves
	int m = 0;						// Variable servant à indiquer le nombre de dés utilisés pour un seul mouvement
	int n = 0;						// Indice de remplissage du tableau tempMoves

	static int nbTour = 1;

	//printf("Tour %d : Début du tour IA de test. On est les %d et les des sont : %d/%d\n",nbTour, OliverJohn.couleur, dices[0], dices[1]);
	nbTour++;	// Incrémentation du nombre de tours
	
	// Si nous sommes les pions noirs alors on inverse les résultats des dés pour partir vers notre but sans changer tous les calculs
	if(OliverJohn.couleur == 0) {
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
		ajustement = 24;
	}
	else
	{
		tirageDes[0] = dices[0];
		tirageDes[1] = dices[1];
	}

	// Si tirage double
	if(dices[0] == dices[1])
	{
		quatreMoves = 1;	// Si le tirage est un double, alors le booléen quatreMoves prend 1
		nbDes = 4;			// Tirage double donc 4 dés utilisables
	}

	nbDices = nbDes;	// Affectation de la copie du nombre de dés disponible


	/*
	##########################################################
	################### Listing Mouvements ###################
	##########################################################
	*/

	// Listing mouvements à faire depuis le bar si il y en a
	// Attribution des mouvements depuis le bar
	//printf("Videau : %d pions\n", gameState->bar[OliverJohn.couleur]);

	// Si on a des pions dans le bar
	if(gameState->bar[OliverJohn.couleur] > 0)
	{
		for(i = 0; i < gameState->bar[OliverJohn.couleur]; i++)		// Parmis les pions dans notre bar
		{
			// Si le tirage n'est pas un double
			if(quatreMoves != 1)
			{
				// EN UTILISANT 1 DE
				for(m = 0; m < 2; m++)	// Boucle pour prendre en compte les deux dés séparément (d'abord en utilisant le premier puis le deuxième)
				{
					//printf("BAR : m : %d pion : %d, avec %d\n", m, i, i-tirageDes[m]);
					// Si la case d'arrivée est à moi OU neutre alors mouvement possible
					if(gameState->board[ajustement+tirageDes[m]].owner == OliverJohn.couleur || gameState->board[ajustement+tirageDes[m]].owner == -1)
					{
						//printf("1 - La cellule %d semble m'appartenir\n", i);
						//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = ajustement+tirageDes[m];				// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

						//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
					// Si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
					else if((gameState->board[ajustement+tirageDes[m]].owner != OliverJohn.couleur && gameState->board[ajustement+tirageDes[m]].nbDames == 1)  || gameState->board[ajustement+tirageDes[m]].owner == -1)
					{
						//printf("2 - La cellule %d semble m'appartenir\n", i);
						//printf("2 - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = ajustement+tirageDes[m];				// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement

						//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
				}
				// EN UTILISANT 2 DES
				// Si la case d'arrivée est à moi OU neutre alors mouvement possible
				if(gameState->board[ajustement+tirageDes[0]+tirageDes[1]].owner == OliverJohn.couleur || gameState->board[ajustement+tirageDes[0]+tirageDes[1]].owner == -1)
				{
					//printf("1 - La cellule %d semble m'appartenir\n", i);
					//printf("1 - La cellule %d est atteignable\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = -1;											// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = ajustement+tirageDes[0]+tirageDes[1];		// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);		// Calcul du coefficient de priorité de ce mouvement

					//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					
					k++;																		// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
				// Si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
				else if((gameState->board[ajustement+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[ajustement+tirageDes[0]+tirageDes[1]].nbDames == 1)  || gameState->board[ajustement+tirageDes[0]+tirageDes[1]].owner == -1)
				{
					//printf("2 - La cellule %d semble m'appartenir\n", i);
					//printf("2 - La cellule %d non par contre\n",
					//i+tirageDes[0]);
					mouvts[k].mouvement.src_point = -1;											// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = ajustement+tirageDes[0]+tirageDes[1];		// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);		// Calcul du coefficient de priorité de ce mouvement

					//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					k++;																		// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
			}
			else
			{
				for(m = 1; m < 5; m++)	// Boucle pour prendre en compte les trois utilisations possibles des dés (en utilisant 1 dé, 2 dés, puis 3 dés puis 4 dés)
				{
					// SOIT la case d'arrivée m'appartient SOIT elle est neutre
					if(gameState->board[ajustement+m*tirageDes[0]].owner == OliverJohn.couleur  || gameState->board[ajustement+m*tirageDes[0]].owner == -1)
					{
						//printf("5 - La cellule %d semble m'appartenir\n", i);
						//printf("5 - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = ajustement+m*tirageDes[0];				// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
						
						//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
					// SOIT la case d'arrivée ne m'appartient pas ET il n'y a qu'un pion ennemi dessus OU elle est neutre
					else if((gameState->board[ajustement+m*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[ajustement+m*tirageDes[0]].nbDames == 1) || gameState->board[ajustement+m*tirageDes[0]].owner == -1)
					{
						//printf("5' - La cellule %d semble m'appartenir\n", i);
						//printf("5' - La cellule %d non par contre\n", i+tirageDes[0]);
						mouvts[k].mouvement.src_point = -1;										// Sauvegarde du numéro de la case de départ
						mouvts[k].mouvement.dest_point = ajustement+m*tirageDes[0];				// Sauvegarde du numéro de la case d'arrivée
						mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement						
						
						//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
						k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
					}
				}
			}
		}
	}



	// Listing pour tous nos pions du plateau
	for(i = 0; i < 24; i++)	// Parmis les cases du plateau
	{
		//printf("///// Je travaille sur la cellule %d, appartenant à %d\n", i, gameState->board[i].owner);
		// Si le tirage n'est pas un double
		if(quatreMoves != 1)
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
				//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
				//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
				//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
				//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
				//printf("Double mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
				//printf("Double mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
				indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
				k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
			}
		}
		// Si le tirage est un double
		else
		{
			for(m = 1; m < 5; m++)	// Boucle pour prendre en compte les trois utilisations possibles des dés (en utilisant 1 dé, 2 dés, puis 3 dés puis 4 dés)
			{
				//printf("m : %d, case : %d, dest : %d\n", m, i, i+m*tirageDes[0]);
				// Si la case de départ m'appartient ET SOIT la case d'arrivée m'appartient SOIT elle est neutre
				if(gameState->board[i].owner == OliverJohn.couleur && ( gameState->board[i+m*tirageDes[0]].owner == OliverJohn.couleur  || gameState->board[i+m*tirageDes[0]].owner == -1 || (i+m*tirageDes[0] < 0)))
				{
					//printf("5 - La cellule %d semble m'appartenir\n", i);
					//printf("5 - La cellule %d non par contre\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = i+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
					//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
					indiceDernierPion = i;													// Actualisation indice du pion le plus éloigné du out
					k++;																	// Incrémentation de l'indice de remplissage du tableau des mouvements possibles
				}
				// Si la case de départ m'appartient ET si la case d'arrivée n'est pas à moi ET qu'il n'y a qu'un seul pion ennemi dessus OU si la case est neutre alors mouvement possible
				else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+m*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[i+m*tirageDes[0]].nbDames == 1) || gameState->board[i+m*tirageDes[0]].owner == -1 || (i+m*tirageDes[0] < 0)))
				{
					//printf("5' - La cellule %d semble m'appartenir\n", i);
					//printf("5' - La cellule %d non par contre\n", i+tirageDes[0]);
					mouvts[k].mouvement.src_point = i;										// Sauvegarde du numéro de la case de départ
					mouvts[k].mouvement.dest_point = i+m*tirageDes[0];						// Sauvegarde du numéro de la case d'arrivée
					mouvts[k].priorite = definePriority(gameState, mouvts[k].mouvement);	// Calcul du coefficient de priorité de ce mouvement
					//printf("Mouvement possibles de %d vers %d de prio : %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point, mouvts[k].priorite);
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
	
	/* Choisit le mouvement en fonction des dés utilisés et selon la priorité de chaque mouvement,
	on sonde d'abord les mouvements de priorité 1, puis on icrémente le compteur de priorité  pour sonder les priorités plus hautes*/
	while(prio < 8)	// Tant que nous n'avons pas étudié les mouvements de chaque priorité
	{
		//printf("## Verif les prio %d\n", prio);
		for(i = 0; i < k; i++)	// Parmis les mouvements de mouvts (indice k non remis à zéro donc on a la taille réel des infos de mouvts)
		{
			//printf("Je travaille sur %d à %d de prio %d\n", mouvts[i].mouvement.src_point, mouvts[i].mouvement.dest_point, mouvts[i].priorite);

			// Si la priorité du mouvmeent en cours d'étude correspond à la priorité en étude
			if(mouvts[i].priorite == prio)
			{
				nbPions = copieGameState.board[mouvts[i].mouvement.src_point].nbDames;	// Sauvegarde du nombre de pions sur la case de départ en étude

				// Si l'indice de la case d'arrivée est inférieure à 0, c'est à dire si le mouvement est en dehors du plateau après le out
				if(mouvts[i].mouvement.dest_point < 0)
				{
					//printf("# Calcul distance dest < 0\n");
					distance = -mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point;	// Calcul de la distance en prenant l'opposé de chaque indice pour obtenir un résultat correct pour l'étude avec les dés
				}
				else
				{
					//printf("# Distance sinon...");
					distance = mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point;	// Sinon calcul de la distance en prenant uniquement l'opposé de l'indice de la case de départ
				}

				// Si l'indice de la case de départ est égal à -1, donc si le pion pars du bar
				if(mouvts[i].mouvement.src_point == -1)
				{
					// Si on contrôle les pions noirs
					if(OliverJohn.couleur == 0)
					{
						distance = mouvts[i].mouvement.dest_point - 24;				// Calcul de la distance à partir de la case 24
					}
					// Si on contrôle les pions blancs
					else
					{
						distance = mouvts[i].mouvement.dest_point+1;				// Calcul de la distance à partir de 0
					}

					nbPions = copieGameState.bar[OliverJohn.couleur];
					//printf("# Distance videau ! avec %d pions\n", nbPions);
				}

				/*
				=======> ESSAI ALGORITHME OPTIMISANT LES MOUVEMENTS A EFFECTUER <========
					-> si des mouvements ont été choisis mais qu'il reste encore des dés non utilisés, sélectionne un mouvement utilisant plus de dés et remplace les mouvements utilisant un seul dé
				
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

				//printf("\tJe rentre dans le if avec %d des et ecart : %d et %d pions et pion le plus loin est %d\n", nbDes, distance, nbPions, indiceDernierPion);

				// Mouvement utilisant 1 seul dé
				// Si tempMoves n'est pas encore rempli (n) ET qu'il me reste encore 1 dé à utiliser ET la distance est bien égale à la valeur d'un dé ET qu'il y a encore des pions sur la case
				if((n < 5 && nbDes >= 1 && (distance == tirageDes[0] || distance == tirageDes[1]) && nbPions > 0) && (tirageDes[0] != -100 || tirageDes[1] != -100))
				{
					// Si la case d'arrivée du mouvement est plus grande que 24 OU bien plus petite que 0
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						// Si le pion le plus éloigné du out se situe dans le dernier Jan (et donc tous les pions sont bien regroupés dans le dernier Jan et on peut sortir sur le out)
						if(indiceDernierPion < 6)
						{
							//printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;		// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
							tempMoves[n].mouvement.dest_point = 25;									// Sauvegarde de la case d'arrivée dans tempMoves (25 car le mouvement peut avoir une case négative)
							tempMoves[n].priorite = mouvts[i].priorite;								// Sauvegarde du coefficient de priorité dans tempMoves
							//printf("\t\t1 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes--;																// Décrémentation du nombre de dés de 1
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;			// Mise à jour de la copie du gameState pour le nombre de pions sur la case

							// Si la priorité est 1
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;							// Décrémentation du nombre de pions dans le bar de notre joueur
							}

							// Si le mouvement nécessite le premier dé dans le cas d'un tirage simple
							if(distance == tirageDes[0] && quatreMoves == 0)
							{
								tirageDes[0] = -100;												// Mise à jour de la valeur de la copie du premier dé à -100 pour indiquer qu'il a été utilisé et ainsi ne pas le réutiliser dans un autre mouvement
							}
							else if(distance == tirageDes[1] && quatreMoves == 0)					// Sinon si le tirage nécessite le second dé dans le cas d'un tirage simple
							{
								tirageDes[1] = -100;												// Mise à jour de la valeur de la copie du second dé à -100 pour indiquer qu'il a été utilisé et ainsi ne pas le réutiliser dans un autre mouvement
							}

							n++;	// Incrémentation de l'indice de remplissage du tableau tempMoves
							//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					// Si la case d'arrivée du mouvement est comprise entre 24 et 0, donc un mouvement sur le plateau de jeu
					else
					{
						//printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;			// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;		// Sauvegarde de la case d'arrivée dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].priorite = mouvts[i].priorite;;								// Sauvegarde du coefficient de priorité dans tempMoves
						//printf("\t\t1 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes--;																	// Décrémentation du nombre de dés de 1
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;				// Mise à jour de la copie du gameState pour le nombre de pions sur la case

						// Si la priorité est 1
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;								// Décrémentation du nombre de pions dans le bar de notre joueur
						}

						// Si le mouvement nécessite le premier dé dans le cas d'un tirage simple
						if(distance == tirageDes[0] && quatreMoves == 0)
						{
							tirageDes[0] = -100;													// Mise à jour de la valeur de la copie du premier dé à -100 pour indiquer qu'il a été utilisé et ainsi ne pas le réutiliser dans un autre mouvement
						}
						else if(distance == tirageDes[1] && quatreMoves == 0)						// Sinon si le tirage nécessite le second dé dans le cas d'un tirage simple
						{
							tirageDes[1] = -100;													// Mise à jour de la valeur de la copie du second dé à -100 pour indiquer qu'il a été utilisé et ainsi ne pas le réutiliser dans un autre mouvement
						}

						n++;	// Incrémentation de l'indice de remplissage du tableau tempMoves
						//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
				// Mouvement utilsant 2 dés
				// Si tempMoves n'est pas encore rempli (n) ET qu'il me reste encore 2 dés à utiliser ET la distance est bien égale à la somme des 2 dés ET que j'ai encore les 2 dés inutilisés
				else if((n < 5 && nbDes >= 2 && (distance == tirageDes[0]+tirageDes[1]) && nbPions > 0) && (tirageDes[0] != -100 && tirageDes[1] != -100))
				{
					// Si la case d'arrivée de ce mouvement est en dehors du plateau de jeu
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							//printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;			// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
							tempMoves[n].mouvement.dest_point = 25;										// Sauvegarde de la case d'arrivée dans tempMoves (25 car le mouvement peut avoir une case négative)
							tempMoves[n].priorite = mouvts[i].priorite;									// Sauvegarde du coefficient de priorité dans tempMoves
							//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=2;																	// Décrémentation du nombre de dés de 2
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;				// Mise à jour de la copie du gameState pour le nombre de pions sur la case

							// Si la priorité est 1
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;								// Décrémentation du nombre de pions dans le bar de notre joueur
							}

							// Si on est dans le cas d'un mouvement simple
							if(quatreMoves == 0)
							{
								// Mise à jour de la valeur des dés pour ne pas les réutiliser 2 fois
								tirageDes[1] = -100;
								tirageDes[0] = -100;
							}

							n++;	// Incrémentation de l'indice de remplissage du tableau tempMoves
							//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					// Si la case d'arrivée de ce mouvement est comprise dans le plateau de jeu
					else
					{
						//printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;			// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;		// Sauvegarde de la case d'arrivée dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].priorite = mouvts[i].priorite;;								// Sauvegarde du coefficient de priorité dans tempMoves
						//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=2;																	// Décrémentation du nombre de dés de 2
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;				// Mise à jour de la copie du gameState pour le nombre de pions sur la case

						// Si la priorité est 1
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;								// Décrémentation du nombre de pions dans le bar de notre joueur
						}

						// Si on est dans le cas d'un mouvement simple
						if(quatreMoves == 0)
						{
							// Mise à jour de la valeur des dés pour ne pas les réutiliser 2 fois
							tirageDes[1] = -100;
							tirageDes[0] = -100;
						}

						n++;	// Incrémentation de l'indice de remplissage du tableau tempMoves
						//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
				// Si tempMoves n'est pas encore rempli (n) ET qu'il me reste encore 3 dés à utiliser ET la distance est bien égale à la somme de 3 dés
				else if(n < 5 && nbDes >= 3 && (distance == 3*tirageDes[0]) && nbPions > 0)
				{
					// Si la case d'arrivée du mouvement est hors du plateau de jeu
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							//printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;			// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
							tempMoves[n].mouvement.dest_point = 25;										// Sauvegarde de la case d'arrivée dans tempMoves (25 car le mouvement peut avoir une case négative)
							tempMoves[n].priorite = mouvts[i].priorite;									// Sauvegarde du coefficient de priorité dans tempMoves
							//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=3;																	// Décrémentation du nombre de dés de 3
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;				// Mise à jour de la copie du gameState pour le nombre de pions sur la case
							// Si la priorité est 1
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;								// Décrémentation du nombre de pions dans le bar de notre joueur
							}
							n++;																		// Incrémentation de l'indice de remplissage du tableau tempMoves
							//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					// Si la case d'arrivée de ce mouvement est comprise dans le plateau de jeu
					else
					{
						//printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;				// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;			// Sauvegarde de la case d'arrivée dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].priorite = mouvts[i].priorite;;									// Sauvegarde du coefficient de priorité dans tempMoves
						//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=3;																		// Décrémentation du nombre de dés de 3
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;					// Mise à jour de la copie du gameState pour le nombre de pions sur la case
						// Si la priorité est 1
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;									// Décrémentation du nombre de pions dans le bar de notre joueur
						}
						n++;																			// Incrémentation de l'indice de remplissage du tableau tempMoves
						//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
					
				}
				// Si tempMoves n'est pas encore rempli (n) ET qu'il me reste encore 4 dés à utiliser ET la distance est bien égale à la somme de 4 dés
				else if(n < 5 && nbDes >= 4 && (distance == 4*tirageDes[0]) && nbPions > 0)
				{
					// Si la case d'arrivée du mouvement est hors du plateau de jeu
					if((mouvts[i].mouvement.dest_point > 24 || mouvts[i].mouvement.dest_point <= 0))
					{
						if(indiceDernierPion < 6)
						{
							//printf("\t\t----- Mouvement vers out\n");
							tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;			// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
							tempMoves[n].mouvement.dest_point = 25;										// Sauvegarde de la case d'arrivée dans tempMoves (25 car le mouvement peut avoir une case négative)
							tempMoves[n].priorite = mouvts[i].priorite;									// Sauvegarde du coefficient de priorité dans tempMoves
							//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
							nbDes-=4;																	// Décrémentation du nombre de dés de 4
							copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;				// Mise à jour de la copie du gameState pour le nombre de pions sur la case
							// Si la priorité est 1
							if(prio == 1)
							{
								copieGameState.bar[OliverJohn.couleur]--;								// Décrémentation du nombre de pions dans le bar de notre joueur
							}
							n++;																		// Incrémentation de l'indice de remplissage du tableau tempMoves
							//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
						}
					}
					// Si la case d'arrivée de ce mouvement est comprise dans le plateau de jeu
					else
					{
						//printf("\t\t----- Mouvement normal\n");
						tempMoves[n].mouvement.src_point = mouvts[i].mouvement.src_point+1;				// Sauvegarde de la case de départ dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].mouvement.dest_point = mouvts[i].mouvement.dest_point+1;			// Sauvegarde de la case d'arrivée dans tempMoves (+1 pour correspondre avecl'indexage de l'interface graphique)
						tempMoves[n].priorite = mouvts[i].priorite;;									// Sauvegarde du coefficient de priorité dans tempMoves
						//printf("\t\t2 - Je travaille sur %d à %d de prio %d\n", tempMoves[n].mouvement.src_point, tempMoves[n].mouvement.dest_point, tempMoves[n].priorite);
						nbDes-=4;																		// Décrémentation du nombre de dés de 4
						copieGameState.board[mouvts[i].mouvement.src_point].nbDames--;					// Mise à jour de la copie du gameState pour le nombre de pions sur la case
						// Si la priorité est 1
						if(prio == 1)
						{
							copieGameState.bar[OliverJohn.couleur]--;									// Décrémentation du nombre de pions dans le bar de notre joueur
						}
						n++;																			// Incrémentation de l'indice de remplissage du tableau tempMoves
						//printf("\t\tJ'ajoute %d à %d de prio : %d avec %d pions restants, il me reste %d des\n", tempMoves[n-1].mouvement.src_point, tempMoves[n-1].mouvement.dest_point, tempMoves[n-1].priorite, copieGameState.board[mouvts[i].mouvement.src_point].nbDames, nbDes);
					}
				}
			}
		}
		prio++;	// Incrémentation du coefficient de priorité
	}

	// Si il reste des dés non utilisés ET  que le pion le plus éloigné n'est pas dans le dernier Jan
	/*if(nbDes > 0 && (indiceDernierPion < 6))
	{
		//printf("JE NE PEUX PAS BOUGER !\n");
		return;		// Je ne peux donc pas faire de déplacements, je quitte la fonction PlayTurn
	}*/

	// Remplissage du tableau final des mouvements à faire
	for(i = 0; i < n; i++)	// Parmis les mouvements du tableau tempMoves
	{
		moves[i].src_point = tempMoves[i].mouvement.src_point;		// Affectation de la case de départ
		moves[i].dest_point = tempMoves[i].mouvement.dest_point;	// Affectation de la case d'arrivée
		*nbMove = n;												// Affectation du nombre de mouvements effectués, pour linterface graphique
		//printf("Je me déplace de %d à %d avec %d moves\n", moves[i].src_point, moves[i].dest_point, *nbMove);
	}

	//printf("Des : %d / %d --- ", dices[0], dices[1]);
	//printf("Tour IA de test terminé Bouyah ! A toi de jouer.\n");
}