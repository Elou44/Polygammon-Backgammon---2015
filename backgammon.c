#include "backgammon.h"
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////
// Dans la librairie
//


/* PETIT COMMENTAIRE VOIR SI CA MARCHE LE PULL */

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
	int priorite;					// Numéros de cases accessibles en plusieurs mouvements
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

int definePriority(int AlliedSquares[2][15], int EnnemySquares[2][15], SMove mov, unsigned int couleur) {	// Définit le coefficient de priorité du mouvement décrit par le SMove donné en paramètre

// /!\ Comment on fait pour les mouvements composés ?
//Est-ce que le move en parametre est forcement valide ou est-ce que'on regarde s'il l'est ?

	int i = 0;	// Indice de parcours de tableau
	int IndiceCaseDepart;	// Numéro de la case de départ en étude
	int IndiceCaseArrivee;	// Numéro de la case d'arrivée en étude
	int bar, out;
	if(couleur == 0) {
		bar = 25; out = 0;
	} else {
		bar = 0; out = 25;
	}
	
	// On cherche l'indice dans AlliedSquares de la case de départ
	if((i = verifPresence(AlliedSquares[1], mov.src_point, 15)) != -1 )	// Si la case de départ est une case conquise, ce qui va forcément être le cas, juste pour avoir l'indice de la case dans AlliedSquares via verifPresence
	{
		IndiceCaseDepart = i;
	}
	
	// PRIORITE 1 : mouvement d'un pion depuis notre bar
	if(mov.src_point == 0) { return 1; }	// Si le point de départ du mouvement est dans le bar (il a été mangé) <- dans LE bar ?
	
	
	
	// On cherche l'indice de la case d'arrivée
	if((i = verifPresence(AlliedSquares[1], mov.dest_point, 15)) != -1 )	// Si la case d'arrivée est une case conquise
	{
		
		IndiceCaseArrivee = i;
		// PRIORITE 2 : mouvement d'un pion isolé vers une case conquise
		if((AlliedSquares[1][IndiceCaseDepart] == 1) || (AlliedSquares[1][IndiceCaseArrivee] == 1 && AlliedSquares[1][IndiceCaseDepart] > 2))	// Si on a un pion tout seul sur une case et que la case d'arrivée est à nous
		//Comment on gère pour les quarts ? (1-6; 7-12; 13-18; 19-24 , mais le sens dépend de la couleur)
		{
			return 2;
		}
		
			// PRIORITE 6 : mouvement d'un pion sécurisé vers une case sécurisée
		if(AlliedSquares[1][IndiceCaseDepart] > 2 && AlliedSquares[1][IndiceCaseArrivee] > 2)
		{
			return 6;
		}
		
	}
	else if((i = verifPresence(EnnemySquares[1], mov.dest_point, 15)) != -1 )
	{
		IndiceCaseArrivee = i;
		
		
		// PRIORITE 7 : mouvement d'un pion non sécurisé pour manger un pion adverse
		if(AlliedSquares[1][IndiceCaseDepart] == 1 && EnnemySquares[1][IndiceCaseArrivee] == 1)	// Si on a un pion isolé et qu'il a la possibilité de manger un pion adverse
		{
			return 7;
		}
		
		// PRIORITE 8 : mouvement d'un pion sécurisé pour manger un adversaire
		if(AlliedSquares[1][IndiceCaseDepart] > 1 && EnnemySquares[1][IndiceCaseArrivee] == 1)
		{
			return 8;
		}
		
	}
	//la case n'appartient ni aux alliés, ni aux ennemis
	
	// Définition des priorités
	
	
	// PRIORITE 3 : mouvement de deux pions sur différentes cases formant une case sécurisée, pas pris en compte dans cette fonction déterminé après dans PlayTurn()
	
	// PRIORITE 4 : mouvement d'un pion pouvant manger un pion adverse, à faire dehors
	
	// PRIORITE 5 : mouvement d'un pion sur une case où on a un pion isolé : obsolète
	
	// PRIORITE 9 : mouvement d'un pion vers le out
	if(mov.dest_point >= out)
	{
		return 9;
	}
	
	// PRIORITE 10 : mouvement par défaut
	return 10;
	
	
	//j'ai changé des trucs dans les priorités, faut qu'on en reparle
	//on peut garder celle-là, qui est assez simple pour les tests, mais faut pas qu'on tarde trop si on veut faire ce qu'on a dit
	
}


void InitLibrary(char name[50])
{
	printf("Initiating library...\n");
	//strcpy();
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
void PlayTest(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{
	int casesAllies[2][15];			// Tableau des cases qui nous appartiennent, Numéro de la case et le nombre de Dames présentes
	int casesEnnemies[2][15];		// Tableau des cases ennemis, numéro de la case et le nombre de Dames présentes
	Mouvements mouvts[60];			// Liste des mouvements possibles
	int i, quatreMoves = 0;			// Indice de parcours de boucle, booléen indiquant si le tirage de dés est un double
	int tirageDes[2];				// Copie du tirage de dés
	int j = 0, k = 0, l = 0;		// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies, indice remplissage tableau moves

	printf("Début du tour IA de test. On est les %d et les des sont : %d/%d\n", OliverJohn.couleur, dices[0], dices[1]);
	
	/*
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les résultats des dés pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}
	*/

	for(i = 0; i < 25; i++)
	{
		printf("Je travaille sur la cellule %d, appartenant à %d\n", i, gameState->board[i].owner);
		if(gameState->board[i].owner == OliverJohn.couleur && ( gameState->board[i+dices[0]].owner == OliverJohn.couleur || gameState->board[i+dices[0]].owner == -1 ) )	// Si la case de départ est à moi ET que la case d'arrivée est à moi alors mouvement possible
		{
			printf("1 - La cellule %d semble m'appartenir\n", i);
			printf("1 - La cellule %d aussi\n", i+dices[0]);
			mouvts[k].mouvement.src_point = i;
			mouvts[k].mouvement.dest_point = i+dices[0];
			printf("Mouvement possibles de %d vers %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point);
			k++;
		}
		else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+dices[0]].owner != OliverJohn.couleur && gameState->board[i+dices[0]].nbDames == 1)  || gameState->board[i+dices[0]].owner == -1 ))	// Si la case de départ est à moi ET que la case d'arrivée n'est pas à moi MAIS qu'il a un seul pion dessus alors mouvement possible
		{
			printf("2 - La cellule %d semble m'appartenir\n", i);
			printf("2 - La cellule %d non par contre\n", i+dices[0]);
			mouvts[k].mouvement.src_point = i;
			mouvts[k].mouvement.dest_point = i+dices[0];
			printf("Mouvement possibles de %d vers %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point);
			k++;
		}
		
		if(gameState->board[i].owner == OliverJohn.couleur && ( gameState->board[i+dices[1]].owner == OliverJohn.couleur  || gameState->board[i+dices[1]].owner == -1 ) )
		{
			printf("3 - La cellule %d semble m'appartenir\n", i);
			printf("3 - La cellule %d aussi\n", i+dices[1]);
			mouvts[k].mouvement.src_point = i;
			mouvts[k].mouvement.dest_point = i+dices[1];
			printf("Mouvement possibles de %d vers %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point);
			k++;
		}
		else if(gameState->board[i].owner == OliverJohn.couleur && ( (gameState->board[i+dices[1]].owner != OliverJohn.couleur && gameState->board[i+dices[1]].nbDames == 1)  || gameState->board[i+dices[0]].owner == -1 ))
		{
			printf("4 - La cellule %d semble m'appartenir\n", i);
			printf("4 - La cellule %d non par contre\n", i+dices[1]);
			mouvts[k].mouvement.src_point = i;
			mouvts[k].mouvement.dest_point = i+dices[1];
			printf("Mouvement possibles de %d vers %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point);
			k++;
		}
	}
	
	for(i = 0; i < k; i++)	// Parmis les mouvements de mouvts (indice k non remis à zéro donc on a la taille réel des infos de mouvts)
	{
		if(dices[0] == dices[1] && j <= 3 && mouvts[i].mouvement.dest_point <= 24)	// Si le tirage est un double ET que je n'ai pas encore indiqué 4 mouvements à effectuer
		{
			moves[j].src_point = mouvts[i].mouvement.src_point+1;
			moves[j].dest_point = mouvts[i].mouvement.dest_point+1;
			printf("Je veux faire le mouvement de %d vers %d\n", mouvts[i].mouvement.src_point+1, mouvts[i].mouvement.dest_point+1);
			printf("IA moves de %d vers %d\n", moves[j].src_point, moves[j].dest_point+1);
			*nbMove += 1;
			printf("Sinon valeur de *nbMoves c'est : %d\n", *nbMove);
			j++;
		}
		else if (j <= 1 && mouvts[i].mouvement.dest_point <= 24)	// Si le tirage est simple ET que je n'ai pas encore indiqué 2 mouvements
		{
			moves[j].src_point = mouvts[i].mouvement.src_point+1;
			moves[j].dest_point = mouvts[i].mouvement.dest_point+1;
			printf("Je veux faire le mouvement de %d vers %d\n", mouvts[i].mouvement.src_point+1, mouvts[i].mouvement.dest_point+1);
			printf("IA moves de %d vers %d\n", moves[j].src_point, moves[j].dest_point+1);
			*nbMove += 1;
			printf("Sinon valeur de *nbMoves c'est : %d\n", *nbMove);
			j++;
		}
	}
	
	printf("Tour IA de test terminé Bouyah ! A toi de jouer.\n");
	
}

void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{

	/*
	#############################################
	######### Déclaration des variables #########
	#############################################
	*/

	int casesAllies[2][15];			// Tableau des cases qui nous appartiennent, Numéro de la case et le nombre de Dames présentes
	int casesEnnemies[2][15];		// Tableau des cases ennemis, numéro de la case et le nombre de Dames présentes
	Mouvements mouvts[60];			// Liste des mouvements possibles
	int i, quatreMoves = 0;			// Indice de parcours de boucle, booléen indiquant si le tirage de dés est un double
	int tirageDes[2];				// Copie du tirage de dés
	int nbdices = 0;				// Nombre de dés utilisable après le tirage (double ou non)
	int j = 0, k = 0;				// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies
	int playTurn = 1;				// Booléen indiquant si je peux jouer mon tour ou non, selon si je peux sortir mes pions présents dans le bar ou non
	int nbBar, nbBarSortie, nbDesDispo;
	int actualdicenb;

	printf("Début du tour\n");
	
	// APPAREMMENT ON DOIT PAS S'OCCUPER DES NUMEROS DE CASE, ON SUPPOSE QU'ON COMMENCE TOUJOURS DE 0 A 25
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les résultats des dés pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}
	
	if(tirageDes[0] == tirageDes[1]) quatreMoves = 1;
	
	if(quatreMoves) {	// On attribue la valeur à nombre de dés selon le booléen indiquant un tirage double
		nbdices = 4;
	} else nbdices = 2;

	/*
	#############################################
	#Remplissage tableaux cases Alliées/Ennemies#
	#############################################
	*/

	// Parcours de chaque case du plateau pour repérer les cases à nous ou pas -> Remplissage des tableaux appartenance des cases
	if(gameState->bar[OliverJohn.couleur] > 0) {	// Si nous avons des pions dans le bar (qui ont été mangés)
		casesAllies[0][j] = 0;	// Sauvegarde numéro case
		casesAllies[1][j] = gameState->bar[OliverJohn.couleur];	// Sauvegarde du nombre de pions présents dans le bar
		j++;	// Incrémentation indice pour le remplissage du tableau casesAllies
	}
	if(gameState->bar[OliverJohn.opponent] > 0) {	// Si l'adversaire a des pions se trouvant dans son bar
		casesEnnemies[0][k] = 0;	// Sauvegarde numéro case
		casesEnnemies[1][k] = gameState->bar[OliverJohn.opponent];	// Sauvegarde du nombre de pions présents dans son bar
		k++;	// Incrémentation indice pour le remplissage du tableau casesEnnemies
	}
	
	for (i = 0; i < 24; i++)	// Parmis toutes les cases du jeu (hors bar et out)
	{
		if (gameState->board[i].owner == OliverJohn.couleur)	// Si le proprio de la case (enum Player) est égal à notre couleur
		{
			casesAllies[0][j] = i+1;	// Sauvegarde numéro case
			casesAllies[1][j] = gameState->board[i].nbDames;	// On garde le nombre de pions sur la case
			j++;	// Incrémentation indice pour le remplissage du tableau casesAllies
		}
		else if(gameState->board[i].owner != -1)
		{
			casesEnnemies[0][k] = i+1;	// Sauvegarde numéro case
			casesEnnemies[1][k] = gameState->board[i].nbDames;	// On garde le nombre de pions sur la case
			k++;	// Incrémentation indice pour le remplissage du tableau casesEnnemies
		}
	}

	/*
	#############################################
	##### Listing des mouvements possibles ######
	#############################################
	*/

	k = 0;	// Remise à zéro de l'indice du tableau casesEnnemies, qui servira comme indice pour le tableau mouvts
	
	// Boucle de remplissage de la liste mouvts
	for (j = 0; j < 15; j++)	// Parmis toutes nos cases conquises
	{
		if(quatreMoves == 1) {	// Si le tirage des dés est un double
			
			/* ### MOUVEMENTS EN UTILISANT UN SEUL DÉ ### */
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {
			/* Si la case d'arrivée est à nous ou qu'il y a max 1 pion dessus*/
	
				// On remplit les structures Mouvement du tableau mouvts
				mouvts[k].mouvement.src_point = j+1;	// Sauvegarde du numéro de la case de déârt du mouvement (j+1 car l'attribut board de gameState ne comprend pas les bar et out)
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;	// Sauvegarde du numéro de la case d'arrivée du mouvement
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);		// Attribution d'un coefficient de priorité et sauvegarde
				k++;	// Incrémentation de l'indice du tableau mouvts
			}
			
			/* ### MOUVEMENTS EN UTILISANT DEUX DÉS ### */
			
			if(!(gameState->board[j+2*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+2*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
	deux dés est à nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+2*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT TROIS DÉS ### */
			
			if(!(gameState->board[j+3*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+3*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
	trois dés est à nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+3*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT QUATRE DÉS ### */
			
			
			if(!(gameState->board[j+4*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+4*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
	quatre dés est à nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+4*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			
		} else {	// Cas où le tirage de dés n'est pas un double
			
			/* ### MOUVEMENTS EN UTILISANT LE PREMIER DÉ ### */
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
	un dé est à nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT LE DEUXIEME DÉ ### */
			
			if(!(gameState->board[j+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[1]].nbDames > 1)) {	/* Si la case d'arrivée en utilisant
	deux dés est à nous ET qu'il y a moins d'un pion ennemi dessus */
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[1]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT LES DEUX DÉS ### */
			
			if(!(gameState->board[j+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]+tirageDes[1]].nbDames > 1)) {	/* Si la case
	d'arrivée en utilisant deux dés est à nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+tirageDes[1]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
		}
	}
	
	
	// Pour moi faudrait rajouter une condition ici qui dit que si on a des pions dans le bar et qu'on peut pas les bouger bah on arrête tout on peut pas jouer
	if((nbBar = casesAllies[1][0]) >= 1)	// Si on a le nombre de pions dans le bar est supérieur ou égal à 1
	{
		nbBarSortie = 0;	// Nouvelle variable indiquant combien de pions j'ai sorti
		nbDesDispo = nbdices;	// Nombre de dés encore disponible pour sortir des pions du bar
		int deDispo[2];	// Tableau des valeurs du tirage des dés
		// Remplissage du tableau des valeurs des dés
		deDispo[0] = tirageDes[0];
		deDispo[1] = tirageDes[1];
		
		for(i = 0; i < k; i++)	// Parmis nos mouvements possibles, on en a k (indice de remplissage des mouvements possibles)
		{
			if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[0] + deDispo[1]) && (nbDesDispo >= 2))	// Si le mouvement est de priorité 1 (donc un mouvement de sortie d'un pion du bar) ET qu'il tuilise 2 dés pour sortir
			{
				nbBarSortie += 2;	// Je sors un pion en utilisant 2 dés
				nbDesDispo-=2;
				if(quatreMoves == 0)	// Si le tirage de dés n'est pas un double
				{
					break;	// Je sors du for (c'est bon j'utilise tous mes dés)
				}
			}
			else if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[0]) && (nbDesDispo >= 1) && (deDispo[0] != -1))	// Si le mouvement est de priorité 1 ET que le déplacement utilise le premier dé ET qu'il reste des dés disponibles ET que le dé utilisé n'a pas pour valeur -1, c'est à dire qu'il n'a pas déjà été utilisé
			{
				deDispo[0] = -1;	// On indique que ce dé a été utilisé
				nbBarSortie++;	// Incrémentation du nombre de pions sortis du bar
				nbDesDispo--;	// Décrémentation du nombre de dés disponibles
			}
			else if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[1]) && (nbDesDispo >= 1) && (deDispo[1] != -1))	// Si le mouvement est de priorité 1 ET que le déplacement utilise le deuxième dé ET qu'il reste des dés disponibles ET que le dé utilisé n'a pas pour valeur -1, c'est à dire qu'il n'a pas déjà été utilisé
			{
				deDispo[1] = -1;	// On indique que ce dé a été utilisé
				nbBarSortie++;	// Incrémentation du nombre de pions sortis du bar
				nbDesDispo--;	// Décrémentation du nombre de dés disponibles
			}
			
			if(nbDesDispo == 0)	// Si je n'ai plus de dés disponibles
			{
				break;	// Je sors du for
			}
		}

		if((nbBarSortie == 0) || ( (nbDesDispo > 0) && (nbBarSortie != nbBar) ) )	// Si je n'ai sorti aucun pion du bar OU si j'ai encore des dés de dispo ET que j'ai encore des pions dans le bar
		{
			playTurn = 0;	// Alors mon booléen disant si je peux jouer mon tour ou non prend FALSE
		}
	}
	

	/*
	#############################################
	########## Choix des moves à faire ##########
	#############################################
	*/
	// /!\ on ne peut pas faire de mouvements tant que des pions sont dans la bar
	
	int nomove = 0, tempind = 0, indtri;	// nb dés encore à utiliser ; bouléen pas de mouvement restants ; indice temporaire de remplissage de tempmoves
	int prioritymin = 1, requireddices;		// priorité minimum à regarder ; lancés de dé requis pour le mouvement
	int movesdone = 0;		// nb de move déjà entrés dans le SMove moves
	Mouvements tempmoves[60];	// mouvements à faire, varie au fur et à mesure du parcours des moves
	
	/*
	// TEST
	SMove tmpMoves[60][10];	// Matrice contenant les mouvements possibles ordonnés selon leur priorité (colonnes)
	int indicePrio1 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 1
	int indicePrio2 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 2
	int indicePrio3 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 3
	int indicePrio4 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 4
	int indicePrio5 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 5
	int indicePrio6 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 6
	int indicePrio7 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 7
	int indicePrio8 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 8
	int indicePrio9 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 9
	int indicePrio10 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorité 10
	// FIN TEST
	*/
	
	
	
	
	while(nbdices && !nomove) {	// Tant qu'il nous reste des dés pour bouger ET qu'il y a encore des mouvements à faire
		nomove = 1; //on initialise à vrai, on met à faux si on trouve un mouvement faisable
		
		
		// Je comprends pas parce que si on a des pions dans le bar et qu'ils peuvent pas sortir, alors les mouvements seront pas dans mouvts !
		// C'est pour ça que je voulais tester avant le listing de tous les autres mouvements si on avait des pions dans le bar qui pouvaient pas bouger et ben ça sert à rien de lister les autres et on passe notre tour
		
		// ####### VERSION TEST A DISCUTER #######
		// On crée une matrice dont les colonnes seront les priorités des mouvements et on le remplit en analysant tous les mouvements possibles. Les mouvements de priorité 1 seront dans la colonne 0, priorité 2 colonne 1...
		// On a plus qu'à regarder dans la colonne 0 si on a des mouvements à faire et à les ajouter dans moves, sinon on regarde dans la colonne 1, etc
	
	/*
	if(playTurn == 1)	// Si je peux jouer mon tour, alors je choisis mes mouvements
	{
		// Remplissage matrice tmpMoves
		for(i = 0; i < 60; i++)
		{
			if(mouvts[i].priorite == 1)
			{
				tmpMoves[indicePrio1][0] = mouvts[i];
				indicePrio1++;
			}
			else if(mouvts[i].priorite == 2)
			{
				tmpMoves[indicePrio1][1] = mouvts[i];
				indicePrio2++;
			}
			else if(mouvts[i].priorite == 3)
			{
				tmpMoves[indicePrio1][2] = mouvts[i];
				indicePrio3++;
			}
			else if(mouvts[i].priorite == 4)
			{
				tmpMoves[indicePrio1][3] = mouvts[i];
				indicePrio4++;
			}
			else if(mouvts[i].priorite == 5)
			{
				tmpMoves[indicePrio1][4] = mouvts[i];
				indicePrio5++;
			}
			else if(mouvts[i].priorite == 6)
			{
				tmpMoves[indicePrio1][5] = mouvts[i];
				indicePrio6++;
			}
			else if(mouvts[i].priorite == 7)
			{
				tmpMoves[indicePrio1][6] = mouvts[i];
				indicePrio7++;
			}
			else if(mouvts[i].priorite == 8)
			{
				tmpMoves[indicePrio1][7] = mouvts[i];
				indicePrio8++;
			}
			else if(mouvts[i].priorite == 9)
			{
				tmpMoves[indicePrio1][8] = mouvts[i];
				indicePrio9++;
			}
			else if(mouvts[i].priorite == 10)
			{
				tmpMoves[indicePrio1][9] = mouvts[i];
				indicePrio10++;
			}
		}
		
		
		
		// Remplissage de moves, tableau indiquant les mouvements à effectuer à l'interface graphique
		while(nbdices != 0)	// Tant qu'il me reste des dés à utiliser
		{
			if(indicePrio1 >= 1)	// Si j'ai des mouvements possibles de priorité 1
			{
				moves[l] = tmpMoves[indicePrio1][0];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio1][0].dest_point - tmpMoves[indicePrio1][0].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio1--;	// Décrémentation de l'indice des mouvements de priorité 1
			}
			else if(indicePrio2 >= 1)	// Sino si j'ai des mouvements possibles de priorité 2
			{
				moves[l] = tmpMoves[indicePrio2][1];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio2][1].dest_point - tmpMoves[indicePrio2][1].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio2--;	// Décrémentation de l'indice des mouvements de priorité 2
			}
			else if(indicePrio3 >= 1)	// Sino si j'ai des mouvements possibles de priorité 3
			{
				moves[l] = tmpMoves[indicePrio3][2];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio3][2].dest_point - tmpMoves[indicePrio3][2].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio3--;	// Décrémentation de l'indice des mouvements de priorité 3
			}
			else if(indicePrio4 >= 1)	// Sino si j'ai des mouvements possibles de priorité 4
			{
				moves[l] = tmpMoves[indicePrio4][3];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio4]3].dest_point - tmpMoves[indicePrio4][3].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio4--;	// Décrémentation de l'indice des mouvements de priorité 4
			}
			else if(indicePrio5 >= 1)	// Sino si j'ai des mouvements possibles de priorité 5
			{
				moves[l] = tmpMoves[indicePrio5][4];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio5][4].dest_point - tmpMoves[indicePrio5][4].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio5--;	// Décrémentation de l'indice des mouvements de priorité 5
			}
			else if(indicePrio6 >= 1)	// Sino si j'ai des mouvements possibles de priorité 6
			{
				moves[l] = tmpMoves[indicePrio6][5];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio6][5].dest_point - tmpMoves[indicePrio6][5].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio6--;	// Décrémentation de l'indice des mouvements de priorité 6
			}
			else if(indicePrio7 >= 1)	// Sino si j'ai des mouvements possibles de priorité 7
			{
				moves[l] = tmpMoves[indicePrio7][6];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio7][6].dest_point - tmpMoves[indicePrio7][6].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio7--;	// Décrémentation de l'indice des mouvements de priorité 7
			}
			else if(indicePrio8 >= 1)	// Sino si j'ai des mouvements possibles de priorité 8
			{
				moves[l] = tmpMoves[indicePrio8][7];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio8][7].dest_point - tmpMoves[indicePrio8][7].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio8--;	// Décrémentation de l'indice des mouvements de priorité 8
			}
			else if(indicePrio9 >= 1)	// Sino si j'ai des mouvements possibles de priorité 9
			{
				moves[l] = tmpMoves[indicePrio9][8];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio9][8].dest_point - tmpMoves[indicePrio9][8].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio9--;	// Décrémentation de l'indice des mouvements de priorité 9
			}
			else if(indicePrio10 >= 1)	// Sino si j'ai des mouvements possibles de priorité 10
			{
				moves[l] = tmpMoves[indicePrio10][9];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio10][9].dest_point - tmpMoves[indicePrio10][9].src_point;	// Nombre de dés que le mouvement de tmpMoves étudié nécessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement nécessite d'utiliser deux dés
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 dés à utiliser
				}
				else nbdices--;
				indicePrio10--;	// Décrémentation de l'indice des mouvements de priorité 10
			}
		}
	}
	else	// Sinon je ne peux pas jouer mon tour et choisir mes mouvements
	{
		printf("Aucun mouvement disponible\n");
	}
		// ####### FIN VERSION TEST A VOIR #######
		*/
		
		
		
	
		if(k == 0) {
			printf("Pas de mouvement possible.\n");
			break;
		} else {
			for(i = 0; i < k; i++) {	//Parmi les mouvements possibles
				nomove = 0;
				if(tempind == 0 && mouvts[i].priorite >= prioritymin) {	//pas de mouvements déjà enregistré
					tempmoves[0] = mouvts[i];
					tempind = 1;
				} else if(mouvts[i].priorite < tempmoves[0].priorite && mouvts[i].priorite >= prioritymin) { //mouvement avec une meilleure priorité : on réinitialise le tableau
					tempmoves[0] = mouvts[i];
					tempind = 1;
				} else if(mouvts[i].priorite == tempmoves[0].priorite && mouvts[i].priorite >= prioritymin) { //mouvement avec la même priorité : on ajoute
					tempmoves[tempind] = mouvts[i];
					tempind++;
				}
			}
		}
		if(tempind == 0) { //cas où on a plus de mouvements à faire (on utilise pas tous les dés)
			printf("Pas d'autre mouvement possible.\n");
			nomove = 1;
		} else {	// Cas où on a encore des mouvements à faire
		
			// Vraiment pas facile à relire, je me perds avec toutes ces conditions <- j'avoue
			// Je t'avoue que je comprends pas grand chose
			// Au pire on tri pas les mouvements, on les cherche par priorité et c'est tout, on favorise pas ceux qui utilisent 2 dés ou autre
			
			
			
			// TRI DES MOUVEMENTS A FAIRE
			for(i = 0; i < tempind; i++) { //on parcours les mouvements enregistrés pour les trier en fonction des dés : en premier ceux qui en utilisent le plus, et en effaçant ceux impossibles
				if(nbdices == 0) break; //Si la case de tempmoves est NULL ou nombre de lancer de dés restant est nul alors on a fini de parcourir
				
				//vérification du nombre de dés à utiliser
				
				else {	// Sinon
					requireddices = tempmoves[i].mouvement.dest_point-tempmoves[i].mouvement.src_point; //Nombre de lancer de dés requis égal à à la case d'arrivée moins numéro case de départ (pas nécéssairement positif)
					if(quatreMoves) {	// Cas d'un tirage double
					
						requireddices = requireddices/tirageDes[0]; //positif : nb dés utilisé <= Mais ça peut ne pas tomber juste ? <- non
						if(requireddices <= nbdices) {	// Si on utilise un nombre de dés raisonnable
							if(indtri == 0) { // Si l'indice du tableau tempmoves est nul pas de mouvement triés encore
								tempmoves[0] = tempmoves[i];
								indtri = 1;
								
							} else {
								for(j = indtri-1; j >= 0; j--) { //on parcours les mouvements triés en commençant par la fin (indtri est le nombre de mouvement trié)
									
									actualdicenb = (tempmoves[j].mouvement.dest_point-tempmoves[j].mouvement.src_point)/tirageDes[0];
									if(requireddices > (actualdicenb)) {
										tempmoves[j+1] = tempmoves[j]; //on décale le mouvement
										if(j == 0) { //cas où le mouvement utilise plus de dés que tous ceux déjà triés
											tempmoves[j] = tempmoves[i];
											indtri++;
										}
										
									} else if(requireddices <= (actualdicenb)) {
										tempmoves[j+1] = tempmoves[i]; //on l'enregistre à la suite
										indtri++;
										break;
									}
								}
							}
						}
					}
					
					
					//remplissage du tableau des moves à faire, en remontant les moves qui utilisent le plus de dés : cas dés non doubles
					
					else { //les dés ne sont pas un double
						if(requireddices == tirageDes[0] || requireddices == tirageDes[1] || requireddices == tirageDes[0]+tirageDes[1]) {
							if(indtri == 0) { //pas de mouvement triés encore
								tempmoves[0] = tempmoves[i];
								indtri = 1;
								
							} else {				// /!\ les requireddices peuvent être négatifs, regarder la couleur
								for(j = indtri-1; j >= 0; j--) { //on parcours les mouvements triés en commençant par la fin (indtri est le nombre de mouvement trié)
									actualdicenb = tempmoves[j].mouvement.dest_point-tempmoves[j].mouvement.src_point;
									
									
									if(OliverJohn.couleur == 1) { //cas où les dés sont positifs
										if(requireddices > actualdicenb) {
											tempmoves[j+1] = tempmoves[j]; //on décale le mouvement
											if(j == 0) { //cas où le mouvement utilise plus de dés que tous ceux déjà triés
												tempmoves[j] = tempmoves[i];
												indtri++;
											}
											
										} else if(requireddices <= actualdicenb) {
											tempmoves[j+1] = tempmoves[i]; //on l'enregistre à la suite
											indtri++;
											break;
										}
										
										
										
									} else { //cas où les dés sont négatifs
										if(requireddices < actualdicenb) {			//on utilise plus de dés, mais le score est plus petit (négatif)
											tempmoves[j+1] = tempmoves[j];			//on décale le mouvement
											if(j == 0) {							//cas où le mouvement utilise plus de dés que tous ceux déjà triés
												tempmoves[j] = tempmoves[i];
												indtri++;
											}
											
										} else if(requireddices >= (actualdicenb)) {
											tempmoves[j+1] = tempmoves[i]; //on l'enregistre à la suite
											indtri++;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			
			for(i = 0; i < indtri; i++) { //on parcours les mouvements triés
				if(nbdices == 0) {
					printf("Tous les dés ont été utilisés\n");
					nomove = 1;
					break;
				} else {
					requireddices = tempmoves[i].mouvement.dest_point-tempmoves[i].mouvement.src_point; //pas nécéssairement positif
					if(quatreMoves) {
						requireddices = requireddices/tirageDes[0];					//positif : nb dés utilisé
						if(requireddices <= nbdices) {								//on vérifie qu'on peut faire le move
							moves[movesdone] = tempmoves[i].mouvement;				//on ajoute le move
							movesdone++;											//on incrémente le compte de move joués
							nbdices -= requireddices;								//on décrémente les dés encore non-utilisés
						}
					} else if(requireddices == tirageDes[0] || requireddices == tirageDes[1] || requireddices == tirageDes[0]+tirageDes[1]) {
						moves[movesdone] = tempmoves[i].mouvement;
						movesdone++;
						if(requireddices == tirageDes[0]) {
							tirageDes[0] = 0;
							nbdices--;
						} else if(requireddices == tirageDes[0]) {
							tirageDes[1] = 0;
							nbdices--;
						} else nbdices = 0;								//mettre le nbdices à 0 empêche de reboucler, pas besoin de mettre à 0 les deux lancers
					}
				}
			}
		}
	}

}

/*
 - PRIORITE 1 : condition vérifier si on a des pions de sortis et qu'il faut sortir en priorité (TOP PRIORITE)
 - PRIORITE 2 : mouvement de pions tout seul sur leur case et qu'on peut sécuriser sur une pile		|  Par quart : de l'ennemi vers nous
 	-> si tous les pions adverses sont derriere, toujours securisés
 - PRIORITE 3 : mouvement de deux pions sur des cases différentes pouvant former une case sécurisée
 - PRIORITE 4 : mouvement de pions pouvant bouffer un adversaire (et pouvant être sécurisé après)	|  Resp. : de nous vers l'ennemi
 - PRIORITE 5 : création de case sécurisée
 - PRIORITE 6 : mouvement sécurisé
 - PRIORITE 7 : mouvement d'un pion non sécurisé pour manger un adversaire							| dépend peut-être du quart, à définir ensemble
 - PRIORITE 8 : mouvement non sécurisé d'un pion sécurisé pour manger un adversaire
 - PRIORITE 9 : sortir un pion vers le out
 - PRIORITE 10 : oups, sucks (mouvement par défaut, en dernier recours)
 
 Qu'est-ce qu'on fait des priorités ? on fait des tableaux pour chaque priorités ? on trie par priorité dans un même tableau ? on traite à l'arrache en parcourant les move à chaque fois ?
 
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