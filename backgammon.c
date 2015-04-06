#include "backgammon.h"
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////
// Dans la librairie
//


/* PETIT COMMENTAIRE VOIR SI CA MARCHE LE PULL */

// Apparemment il faut faire une structure globale pour stocker toutes les infos dont on a besoin pour impl�menter nos fonctions

typedef struct {	// Structure d'une IA, regroupant les infos dont on a besoin pour les fonctions et la strat�gie
	char nom[50];					// Nom de l'IA
	unsigned int couleur;			// Couleur des pions de l'IA
	unsigned int opponent;			// Couleur des pions adverses
	unsigned int scoreActuel[2];	// Nombre de manches gagn�es, et celle de l'adversaire
	unsigned int scorePourGagner;	// Nombre de manches n�cessaires pour gagner un match
	unsigned int scoreManche;		// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)
	unsigned int pions;				// Nombre de pions encore sur le plateau
	int mancheActuelle;				// Num�ro de la manche jou�e actuellement
	unsigned int resultatMatch;		// 1 si cette IA a gagn�e, 0 sinon
}IA;


// Sinon on peut aussi regrouper cette structure avec IA
typedef struct {	// Structure d�crivant les mouvements possibles � partir d'une case de d�part (3 moves max)
	SMove mouvement;				// Num�ros de cases accessibles en un mouvement
	int priorite;					// Num�ros de cases accessibles en plusieurs mouvements
}Mouvements;

/*
typedef struct {
	int indice;						// Num�ro de la case
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

int definePriority(int AlliedSquares[2][15], int EnnemySquares[2][15], SMove mov, unsigned int couleur) {	// D�finit le coefficient de priorit� du mouvement d�crit par le SMove donn� en param�tre

// /!\ Comment on fait pour les mouvements compos�s ?
//Est-ce que le move en parametre est forcement valide ou est-ce que'on regarde s'il l'est ?

	int i = 0;	// Indice de parcours de tableau
	int IndiceCaseDepart;	// Num�ro de la case de d�part en �tude
	int IndiceCaseArrivee;	// Num�ro de la case d'arriv�e en �tude
	int bar, out;
	if(couleur == 0) {
		bar = 25; out = 0;
	} else {
		bar = 0; out = 25;
	}
	
	// On cherche l'indice dans AlliedSquares de la case de d�part
	if((i = verifPresence(AlliedSquares[1], mov.src_point, 15)) != -1 )	// Si la case de d�part est une case conquise, ce qui va forc�ment �tre le cas, juste pour avoir l'indice de la case dans AlliedSquares via verifPresence
	{
		IndiceCaseDepart = i;
	}
	
	// PRIORITE 1 : mouvement d'un pion depuis notre bar
	if(mov.src_point == 0) { return 1; }	// Si le point de d�part du mouvement est dans le bar (il a �t� mang�) <- dans LE bar ?
	
	
	
	// On cherche l'indice de la case d'arriv�e
	if((i = verifPresence(AlliedSquares[1], mov.dest_point, 15)) != -1 )	// Si la case d'arriv�e est une case conquise
	{
		
		IndiceCaseArrivee = i;
		// PRIORITE 2 : mouvement d'un pion isol� vers une case conquise
		if((AlliedSquares[1][IndiceCaseDepart] == 1) || (AlliedSquares[1][IndiceCaseArrivee] == 1 && AlliedSquares[1][IndiceCaseDepart] > 2))	// Si on a un pion tout seul sur une case et que la case d'arriv�e est � nous
		//Comment on g�re pour les quarts ? (1-6; 7-12; 13-18; 19-24 , mais le sens d�pend de la couleur)
		{
			return 2;
		}
		
			// PRIORITE 6 : mouvement d'un pion s�curis� vers une case s�curis�e
		if(AlliedSquares[1][IndiceCaseDepart] > 2 && AlliedSquares[1][IndiceCaseArrivee] > 2)
		{
			return 6;
		}
		
	}
	else if((i = verifPresence(EnnemySquares[1], mov.dest_point, 15)) != -1 )
	{
		IndiceCaseArrivee = i;
		
		
		// PRIORITE 7 : mouvement d'un pion non s�curis� pour manger un pion adverse
		if(AlliedSquares[1][IndiceCaseDepart] == 1 && EnnemySquares[1][IndiceCaseArrivee] == 1)	// Si on a un pion isol� et qu'il a la possibilit� de manger un pion adverse
		{
			return 7;
		}
		
		// PRIORITE 8 : mouvement d'un pion s�curis� pour manger un adversaire
		if(AlliedSquares[1][IndiceCaseDepart] > 1 && EnnemySquares[1][IndiceCaseArrivee] == 1)
		{
			return 8;
		}
		
	}
	//la case n'appartient ni aux alli�s, ni aux ennemis
	
	// D�finition des priorit�s
	
	
	// PRIORITE 3 : mouvement de deux pions sur diff�rentes cases formant une case s�curis�e, pas pris en compte dans cette fonction d�termin� apr�s dans PlayTurn()
	
	// PRIORITE 4 : mouvement d'un pion pouvant manger un pion adverse, � faire dehors
	
	// PRIORITE 5 : mouvement d'un pion sur une case o� on a un pion isol� : obsol�te
	
	// PRIORITE 9 : mouvement d'un pion vers le out
	if(mov.dest_point >= out)
	{
		return 9;
	}
	
	// PRIORITE 10 : mouvement par d�faut
	return 10;
	
	
	//j'ai chang� des trucs dans les priorit�s, faut qu'on en reparle
	//on peut garder celle-l�, qui est assez simple pour les tests, mais faut pas qu'on tarde trop si on veut faire ce qu'on a dit
	
}


void InitLibrary(char name[50])
{
	printf("Initiating library...\n");
	//strcpy();
}

void StartMatch(const unsigned int target_score)
{
	printf("Starting match...\n");
	/* En param�tres le nombre de Game � gagner pour remporter le match
	Initialiser l'IA pour un match
	Initialisation du nombre de manches � gagner dans la structure
	Initialisation � 0 du nombre de manches actuelles gagn�es
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
	/* En param�tre l'�num�ration Player disant � qui appartient la case
	Initialiser l'IA pour une manche
	Initialisation du score de la manche � 0
	*/
	OliverJohn.couleur = p;
	if(OliverJohn.couleur == 0) OliverJohn.opponent = 1;
	else OliverJohn.opponent = 0;
	OliverJohn.scoreManche = 0;
	OliverJohn.mancheActuelle++;
}

void EndGame()	// On indique juste que la manche est termin�e, vu qu'on renvoie rien
/* Mais au final je sais pas si on doit afficher un truc, plut�t l'interface graphique
 pour qu'ils le fassent tout beau et tout, on verra pas la console sinon */
{
	printf("EndGame\n");
	printf("Score actuel : %s -> %d points\n", OliverJohn.nom, OliverJohn.scoreActuel[0]);
	
}

void EndMatch()	// On indique juste que le match est termin�
// M�me chose ici, en fait je pense pas qu'on doive print un truc
// 
{
	printf("EndMatch\n");
	printf("Partie termin�e\n");
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
	int casesAllies[2][15];			// Tableau des cases qui nous appartiennent, Num�ro de la case et le nombre de Dames pr�sentes
	int casesEnnemies[2][15];		// Tableau des cases ennemis, num�ro de la case et le nombre de Dames pr�sentes
	Mouvements mouvts[60];			// Liste des mouvements possibles
	int i, quatreMoves = 0;			// Indice de parcours de boucle, bool�en indiquant si le tirage de d�s est un double
	int tirageDes[2];				// Copie du tirage de d�s
	int j = 0, k = 0, l = 0;		// Indices pour remplir les tableaux des cases, respectivement Alli�es / Ennemies, indice remplissage tableau moves

	printf("D�but du tour IA de test. On est les %d et les des sont : %d/%d\n", OliverJohn.couleur, dices[0], dices[1]);
	
	/*
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les r�sultats des d�s pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}
	*/

	for(i = 0; i < 25; i++)
	{
		printf("Je travaille sur la cellule %d, appartenant � %d\n", i, gameState->board[i].owner);
		if(gameState->board[i].owner == OliverJohn.couleur && ( gameState->board[i+dices[0]].owner == OliverJohn.couleur || gameState->board[i+dices[0]].owner == -1 ) )	// Si la case de d�part est � moi ET que la case d'arriv�e est � moi alors mouvement possible
		{
			printf("1 - La cellule %d semble m'appartenir\n", i);
			printf("1 - La cellule %d aussi\n", i+dices[0]);
			mouvts[k].mouvement.src_point = i;
			mouvts[k].mouvement.dest_point = i+dices[0];
			printf("Mouvement possibles de %d vers %d\n", mouvts[k].mouvement.src_point, mouvts[k].mouvement.dest_point);
			k++;
		}
		else if(gameState->board[i].owner == OliverJohn.couleur && ((gameState->board[i+dices[0]].owner != OliverJohn.couleur && gameState->board[i+dices[0]].nbDames == 1)  || gameState->board[i+dices[0]].owner == -1 ))	// Si la case de d�part est � moi ET que la case d'arriv�e n'est pas � moi MAIS qu'il a un seul pion dessus alors mouvement possible
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
	
	for(i = 0; i < k; i++)	// Parmis les mouvements de mouvts (indice k non remis � z�ro donc on a la taille r�el des infos de mouvts)
	{
		if(dices[0] == dices[1] && j <= 3 && mouvts[i].mouvement.dest_point <= 24)	// Si le tirage est un double ET que je n'ai pas encore indiqu� 4 mouvements � effectuer
		{
			moves[j].src_point = mouvts[i].mouvement.src_point+1;
			moves[j].dest_point = mouvts[i].mouvement.dest_point+1;
			printf("Je veux faire le mouvement de %d vers %d\n", mouvts[i].mouvement.src_point+1, mouvts[i].mouvement.dest_point+1);
			printf("IA moves de %d vers %d\n", moves[j].src_point, moves[j].dest_point+1);
			*nbMove += 1;
			printf("Sinon valeur de *nbMoves c'est : %d\n", *nbMove);
			j++;
		}
		else if (j <= 1 && mouvts[i].mouvement.dest_point <= 24)	// Si le tirage est simple ET que je n'ai pas encore indiqu� 2 mouvements
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
	
	printf("Tour IA de test termin� Bouyah ! A toi de jouer.\n");
	
}

void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)
{

	/*
	#############################################
	######### D�claration des variables #########
	#############################################
	*/

	int casesAllies[2][15];			// Tableau des cases qui nous appartiennent, Num�ro de la case et le nombre de Dames pr�sentes
	int casesEnnemies[2][15];		// Tableau des cases ennemis, num�ro de la case et le nombre de Dames pr�sentes
	Mouvements mouvts[60];			// Liste des mouvements possibles
	int i, quatreMoves = 0;			// Indice de parcours de boucle, bool�en indiquant si le tirage de d�s est un double
	int tirageDes[2];				// Copie du tirage de d�s
	int nbdices = 0;				// Nombre de d�s utilisable apr�s le tirage (double ou non)
	int j = 0, k = 0;				// Indices pour remplir les tableaux des cases, respectivement Alli�es / Ennemies
	int playTurn = 1;				// Bool�en indiquant si je peux jouer mon tour ou non, selon si je peux sortir mes pions pr�sents dans le bar ou non
	int nbBar, nbBarSortie, nbDesDispo;
	int actualdicenb;

	printf("D�but du tour\n");
	
	// APPAREMMENT ON DOIT PAS S'OCCUPER DES NUMEROS DE CASE, ON SUPPOSE QU'ON COMMENCE TOUJOURS DE 0 A 25
	if(OliverJohn.couleur == 0) {	// Si nous sommes les pions noirs alors on inverse les r�sultats des d�s pour partir vers notre but sans changer tous les calculs
		tirageDes[0] = -dices[0];
		tirageDes[1] = -dices[1];
	}
	
	if(tirageDes[0] == tirageDes[1]) quatreMoves = 1;
	
	if(quatreMoves) {	// On attribue la valeur � nombre de d�s selon le bool�en indiquant un tirage double
		nbdices = 4;
	} else nbdices = 2;

	/*
	#############################################
	#Remplissage tableaux cases Alli�es/Ennemies#
	#############################################
	*/

	// Parcours de chaque case du plateau pour rep�rer les cases � nous ou pas -> Remplissage des tableaux appartenance des cases
	if(gameState->bar[OliverJohn.couleur] > 0) {	// Si nous avons des pions dans le bar (qui ont �t� mang�s)
		casesAllies[0][j] = 0;	// Sauvegarde num�ro case
		casesAllies[1][j] = gameState->bar[OliverJohn.couleur];	// Sauvegarde du nombre de pions pr�sents dans le bar
		j++;	// Incr�mentation indice pour le remplissage du tableau casesAllies
	}
	if(gameState->bar[OliverJohn.opponent] > 0) {	// Si l'adversaire a des pions se trouvant dans son bar
		casesEnnemies[0][k] = 0;	// Sauvegarde num�ro case
		casesEnnemies[1][k] = gameState->bar[OliverJohn.opponent];	// Sauvegarde du nombre de pions pr�sents dans son bar
		k++;	// Incr�mentation indice pour le remplissage du tableau casesEnnemies
	}
	
	for (i = 0; i < 24; i++)	// Parmis toutes les cases du jeu (hors bar et out)
	{
		if (gameState->board[i].owner == OliverJohn.couleur)	// Si le proprio de la case (enum Player) est �gal � notre couleur
		{
			casesAllies[0][j] = i+1;	// Sauvegarde num�ro case
			casesAllies[1][j] = gameState->board[i].nbDames;	// On garde le nombre de pions sur la case
			j++;	// Incr�mentation indice pour le remplissage du tableau casesAllies
		}
		else if(gameState->board[i].owner != -1)
		{
			casesEnnemies[0][k] = i+1;	// Sauvegarde num�ro case
			casesEnnemies[1][k] = gameState->board[i].nbDames;	// On garde le nombre de pions sur la case
			k++;	// Incr�mentation indice pour le remplissage du tableau casesEnnemies
		}
	}

	/*
	#############################################
	##### Listing des mouvements possibles ######
	#############################################
	*/

	k = 0;	// Remise � z�ro de l'indice du tableau casesEnnemies, qui servira comme indice pour le tableau mouvts
	
	// Boucle de remplissage de la liste mouvts
	for (j = 0; j < 15; j++)	// Parmis toutes nos cases conquises
	{
		if(quatreMoves == 1) {	// Si le tirage des d�s est un double
			
			/* ### MOUVEMENTS EN UTILISANT UN SEUL D� ### */
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {
			/* Si la case d'arriv�e est � nous ou qu'il y a max 1 pion dessus*/
	
				// On remplit les structures Mouvement du tableau mouvts
				mouvts[k].mouvement.src_point = j+1;	// Sauvegarde du num�ro de la case de d��rt du mouvement (j+1 car l'attribut board de gameState ne comprend pas les bar et out)
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;	// Sauvegarde du num�ro de la case d'arriv�e du mouvement
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);		// Attribution d'un coefficient de priorit� et sauvegarde
				k++;	// Incr�mentation de l'indice du tableau mouvts
			}
			
			/* ### MOUVEMENTS EN UTILISANT DEUX D�S ### */
			
			if(!(gameState->board[j+2*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+2*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arriv�e en utilisant
	deux d�s est � nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+2*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT TROIS D�S ### */
			
			if(!(gameState->board[j+3*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+3*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arriv�e en utilisant
	trois d�s est � nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+3*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT QUATRE D�S ### */
			
			
			if(!(gameState->board[j+4*tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+4*tirageDes[0]].nbDames > 1)) {	/* Si la case d'arriv�e en utilisant
	quatre d�s est � nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+4*tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			
		} else {	// Cas o� le tirage de d�s n'est pas un double
			
			/* ### MOUVEMENTS EN UTILISANT LE PREMIER D� ### */
			
			if(!(gameState->board[j+tirageDes[0]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]].nbDames > 1)) {	/* Si la case d'arriv�e en utilisant
	un d� est � nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT LE DEUXIEME D� ### */
			
			if(!(gameState->board[j+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[1]].nbDames > 1)) {	/* Si la case d'arriv�e en utilisant
	deux d�s est � nous ET qu'il y a moins d'un pion ennemi dessus */
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[1]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
			
			/* ### MOUVEMENTS EN UTILISANT LES DEUX D�S ### */
			
			if(!(gameState->board[j+tirageDes[0]+tirageDes[1]].owner != OliverJohn.couleur && gameState->board[j+tirageDes[0]+tirageDes[1]].nbDames > 1)) {	/* Si la case
	d'arriv�e en utilisant deux d�s est � nous ET qu'il y a moins d'un pion ennemi dessus */
	
				mouvts[k].mouvement.src_point = j+1;
				mouvts[k].mouvement.dest_point = j+tirageDes[0]+tirageDes[1]+1;
				mouvts[k].priorite = definePriority(casesAllies, casesEnnemies, mouvts[k].mouvement, OliverJohn.couleur);
				k++;
			}
		}
	}
	
	
	// Pour moi faudrait rajouter une condition ici qui dit que si on a des pions dans le bar et qu'on peut pas les bouger bah on arr�te tout on peut pas jouer
	if((nbBar = casesAllies[1][0]) >= 1)	// Si on a le nombre de pions dans le bar est sup�rieur ou �gal � 1
	{
		nbBarSortie = 0;	// Nouvelle variable indiquant combien de pions j'ai sorti
		nbDesDispo = nbdices;	// Nombre de d�s encore disponible pour sortir des pions du bar
		int deDispo[2];	// Tableau des valeurs du tirage des d�s
		// Remplissage du tableau des valeurs des d�s
		deDispo[0] = tirageDes[0];
		deDispo[1] = tirageDes[1];
		
		for(i = 0; i < k; i++)	// Parmis nos mouvements possibles, on en a k (indice de remplissage des mouvements possibles)
		{
			if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[0] + deDispo[1]) && (nbDesDispo >= 2))	// Si le mouvement est de priorit� 1 (donc un mouvement de sortie d'un pion du bar) ET qu'il tuilise 2 d�s pour sortir
			{
				nbBarSortie += 2;	// Je sors un pion en utilisant 2 d�s
				nbDesDispo-=2;
				if(quatreMoves == 0)	// Si le tirage de d�s n'est pas un double
				{
					break;	// Je sors du for (c'est bon j'utilise tous mes d�s)
				}
			}
			else if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[0]) && (nbDesDispo >= 1) && (deDispo[0] != -1))	// Si le mouvement est de priorit� 1 ET que le d�placement utilise le premier d� ET qu'il reste des d�s disponibles ET que le d� utilis� n'a pas pour valeur -1, c'est � dire qu'il n'a pas d�j� �t� utilis�
			{
				deDispo[0] = -1;	// On indique que ce d� a �t� utilis�
				nbBarSortie++;	// Incr�mentation du nombre de pions sortis du bar
				nbDesDispo--;	// D�cr�mentation du nombre de d�s disponibles
			}
			else if((mouvts[i].priorite == 1) && (mouvts[i].mouvement.dest_point - mouvts[i].mouvement.src_point == deDispo[1]) && (nbDesDispo >= 1) && (deDispo[1] != -1))	// Si le mouvement est de priorit� 1 ET que le d�placement utilise le deuxi�me d� ET qu'il reste des d�s disponibles ET que le d� utilis� n'a pas pour valeur -1, c'est � dire qu'il n'a pas d�j� �t� utilis�
			{
				deDispo[1] = -1;	// On indique que ce d� a �t� utilis�
				nbBarSortie++;	// Incr�mentation du nombre de pions sortis du bar
				nbDesDispo--;	// D�cr�mentation du nombre de d�s disponibles
			}
			
			if(nbDesDispo == 0)	// Si je n'ai plus de d�s disponibles
			{
				break;	// Je sors du for
			}
		}

		if((nbBarSortie == 0) || ( (nbDesDispo > 0) && (nbBarSortie != nbBar) ) )	// Si je n'ai sorti aucun pion du bar OU si j'ai encore des d�s de dispo ET que j'ai encore des pions dans le bar
		{
			playTurn = 0;	// Alors mon bool�en disant si je peux jouer mon tour ou non prend FALSE
		}
	}
	

	/*
	#############################################
	########## Choix des moves � faire ##########
	#############################################
	*/
	// /!\ on ne peut pas faire de mouvements tant que des pions sont dans la bar
	
	int nomove = 0, tempind = 0, indtri;	// nb d�s encore � utiliser ; boul�en pas de mouvement restants ; indice temporaire de remplissage de tempmoves
	int prioritymin = 1, requireddices;		// priorit� minimum � regarder ; lanc�s de d� requis pour le mouvement
	int movesdone = 0;		// nb de move d�j� entr�s dans le SMove moves
	Mouvements tempmoves[60];	// mouvements � faire, varie au fur et � mesure du parcours des moves
	
	/*
	// TEST
	SMove tmpMoves[60][10];	// Matrice contenant les mouvements possibles ordonn�s selon leur priorit� (colonnes)
	int indicePrio1 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 1
	int indicePrio2 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 2
	int indicePrio3 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 3
	int indicePrio4 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 4
	int indicePrio5 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 5
	int indicePrio6 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 6
	int indicePrio7 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 7
	int indicePrio8 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 8
	int indicePrio9 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 9
	int indicePrio10 = 0;	// Indice de remplissage de la matrice tmpMoves, colonne priorit� 10
	// FIN TEST
	*/
	
	
	
	
	while(nbdices && !nomove) {	// Tant qu'il nous reste des d�s pour bouger ET qu'il y a encore des mouvements � faire
		nomove = 1; //on initialise � vrai, on met � faux si on trouve un mouvement faisable
		
		
		// Je comprends pas parce que si on a des pions dans le bar et qu'ils peuvent pas sortir, alors les mouvements seront pas dans mouvts !
		// C'est pour �a que je voulais tester avant le listing de tous les autres mouvements si on avait des pions dans le bar qui pouvaient pas bouger et ben �a sert � rien de lister les autres et on passe notre tour
		
		// ####### VERSION TEST A DISCUTER #######
		// On cr�e une matrice dont les colonnes seront les priorit�s des mouvements et on le remplit en analysant tous les mouvements possibles. Les mouvements de priorit� 1 seront dans la colonne 0, priorit� 2 colonne 1...
		// On a plus qu'� regarder dans la colonne 0 si on a des mouvements � faire et � les ajouter dans moves, sinon on regarde dans la colonne 1, etc
	
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
		
		
		
		// Remplissage de moves, tableau indiquant les mouvements � effectuer � l'interface graphique
		while(nbdices != 0)	// Tant qu'il me reste des d�s � utiliser
		{
			if(indicePrio1 >= 1)	// Si j'ai des mouvements possibles de priorit� 1
			{
				moves[l] = tmpMoves[indicePrio1][0];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio1][0].dest_point - tmpMoves[indicePrio1][0].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio1--;	// D�cr�mentation de l'indice des mouvements de priorit� 1
			}
			else if(indicePrio2 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 2
			{
				moves[l] = tmpMoves[indicePrio2][1];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio2][1].dest_point - tmpMoves[indicePrio2][1].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio2--;	// D�cr�mentation de l'indice des mouvements de priorit� 2
			}
			else if(indicePrio3 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 3
			{
				moves[l] = tmpMoves[indicePrio3][2];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio3][2].dest_point - tmpMoves[indicePrio3][2].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio3--;	// D�cr�mentation de l'indice des mouvements de priorit� 3
			}
			else if(indicePrio4 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 4
			{
				moves[l] = tmpMoves[indicePrio4][3];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio4]3].dest_point - tmpMoves[indicePrio4][3].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio4--;	// D�cr�mentation de l'indice des mouvements de priorit� 4
			}
			else if(indicePrio5 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 5
			{
				moves[l] = tmpMoves[indicePrio5][4];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio5][4].dest_point - tmpMoves[indicePrio5][4].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio5--;	// D�cr�mentation de l'indice des mouvements de priorit� 5
			}
			else if(indicePrio6 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 6
			{
				moves[l] = tmpMoves[indicePrio6][5];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio6][5].dest_point - tmpMoves[indicePrio6][5].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio6--;	// D�cr�mentation de l'indice des mouvements de priorit� 6
			}
			else if(indicePrio7 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 7
			{
				moves[l] = tmpMoves[indicePrio7][6];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio7][6].dest_point - tmpMoves[indicePrio7][6].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio7--;	// D�cr�mentation de l'indice des mouvements de priorit� 7
			}
			else if(indicePrio8 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 8
			{
				moves[l] = tmpMoves[indicePrio8][7];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio8][7].dest_point - tmpMoves[indicePrio8][7].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio8--;	// D�cr�mentation de l'indice des mouvements de priorit� 8
			}
			else if(indicePrio9 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 9
			{
				moves[l] = tmpMoves[indicePrio9][8];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio9][8].dest_point - tmpMoves[indicePrio9][8].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio9--;	// D�cr�mentation de l'indice des mouvements de priorit� 9
			}
			else if(indicePrio10 >= 1)	// Sino si j'ai des mouvements possibles de priorit� 10
			{
				moves[l] = tmpMoves[indicePrio10][9];	// J'ajoute le mouvement dans moves
				requireddices = tmpMoves[indicePrio10][9].dest_point - tmpMoves[indicePrio10][9].src_point;	// Nombre de d�s que le mouvement de tmpMoves �tudi� n�cessite
				if(requireddices == (tirageDes[0]+tirageDes[1]) && nbdices >= 2)	// Si le mouvement n�cessite d'utiliser deux d�s
				{
					nbdices =- 2;	// J'indique qu'il me reste moins 2 d�s � utiliser
				}
				else nbdices--;
				indicePrio10--;	// D�cr�mentation de l'indice des mouvements de priorit� 10
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
				if(tempind == 0 && mouvts[i].priorite >= prioritymin) {	//pas de mouvements d�j� enregistr�
					tempmoves[0] = mouvts[i];
					tempind = 1;
				} else if(mouvts[i].priorite < tempmoves[0].priorite && mouvts[i].priorite >= prioritymin) { //mouvement avec une meilleure priorit� : on r�initialise le tableau
					tempmoves[0] = mouvts[i];
					tempind = 1;
				} else if(mouvts[i].priorite == tempmoves[0].priorite && mouvts[i].priorite >= prioritymin) { //mouvement avec la m�me priorit� : on ajoute
					tempmoves[tempind] = mouvts[i];
					tempind++;
				}
			}
		}
		if(tempind == 0) { //cas o� on a plus de mouvements � faire (on utilise pas tous les d�s)
			printf("Pas d'autre mouvement possible.\n");
			nomove = 1;
		} else {	// Cas o� on a encore des mouvements � faire
		
			// Vraiment pas facile � relire, je me perds avec toutes ces conditions <- j'avoue
			// Je t'avoue que je comprends pas grand chose
			// Au pire on tri pas les mouvements, on les cherche par priorit� et c'est tout, on favorise pas ceux qui utilisent 2 d�s ou autre
			
			
			
			// TRI DES MOUVEMENTS A FAIRE
			for(i = 0; i < tempind; i++) { //on parcours les mouvements enregistr�s pour les trier en fonction des d�s : en premier ceux qui en utilisent le plus, et en effa�ant ceux impossibles
				if(nbdices == 0) break; //Si la case de tempmoves est NULL ou nombre de lancer de d�s restant est nul alors on a fini de parcourir
				
				//v�rification du nombre de d�s � utiliser
				
				else {	// Sinon
					requireddices = tempmoves[i].mouvement.dest_point-tempmoves[i].mouvement.src_point; //Nombre de lancer de d�s requis �gal � � la case d'arriv�e moins num�ro case de d�part (pas n�c�ssairement positif)
					if(quatreMoves) {	// Cas d'un tirage double
					
						requireddices = requireddices/tirageDes[0]; //positif : nb d�s utilis� <= Mais �a peut ne pas tomber juste ? <- non
						if(requireddices <= nbdices) {	// Si on utilise un nombre de d�s raisonnable
							if(indtri == 0) { // Si l'indice du tableau tempmoves est nul pas de mouvement tri�s encore
								tempmoves[0] = tempmoves[i];
								indtri = 1;
								
							} else {
								for(j = indtri-1; j >= 0; j--) { //on parcours les mouvements tri�s en commen�ant par la fin (indtri est le nombre de mouvement tri�)
									
									actualdicenb = (tempmoves[j].mouvement.dest_point-tempmoves[j].mouvement.src_point)/tirageDes[0];
									if(requireddices > (actualdicenb)) {
										tempmoves[j+1] = tempmoves[j]; //on d�cale le mouvement
										if(j == 0) { //cas o� le mouvement utilise plus de d�s que tous ceux d�j� tri�s
											tempmoves[j] = tempmoves[i];
											indtri++;
										}
										
									} else if(requireddices <= (actualdicenb)) {
										tempmoves[j+1] = tempmoves[i]; //on l'enregistre � la suite
										indtri++;
										break;
									}
								}
							}
						}
					}
					
					
					//remplissage du tableau des moves � faire, en remontant les moves qui utilisent le plus de d�s : cas d�s non doubles
					
					else { //les d�s ne sont pas un double
						if(requireddices == tirageDes[0] || requireddices == tirageDes[1] || requireddices == tirageDes[0]+tirageDes[1]) {
							if(indtri == 0) { //pas de mouvement tri�s encore
								tempmoves[0] = tempmoves[i];
								indtri = 1;
								
							} else {				// /!\ les requireddices peuvent �tre n�gatifs, regarder la couleur
								for(j = indtri-1; j >= 0; j--) { //on parcours les mouvements tri�s en commen�ant par la fin (indtri est le nombre de mouvement tri�)
									actualdicenb = tempmoves[j].mouvement.dest_point-tempmoves[j].mouvement.src_point;
									
									
									if(OliverJohn.couleur == 1) { //cas o� les d�s sont positifs
										if(requireddices > actualdicenb) {
											tempmoves[j+1] = tempmoves[j]; //on d�cale le mouvement
											if(j == 0) { //cas o� le mouvement utilise plus de d�s que tous ceux d�j� tri�s
												tempmoves[j] = tempmoves[i];
												indtri++;
											}
											
										} else if(requireddices <= actualdicenb) {
											tempmoves[j+1] = tempmoves[i]; //on l'enregistre � la suite
											indtri++;
											break;
										}
										
										
										
									} else { //cas o� les d�s sont n�gatifs
										if(requireddices < actualdicenb) {			//on utilise plus de d�s, mais le score est plus petit (n�gatif)
											tempmoves[j+1] = tempmoves[j];			//on d�cale le mouvement
											if(j == 0) {							//cas o� le mouvement utilise plus de d�s que tous ceux d�j� tri�s
												tempmoves[j] = tempmoves[i];
												indtri++;
											}
											
										} else if(requireddices >= (actualdicenb)) {
											tempmoves[j+1] = tempmoves[i]; //on l'enregistre � la suite
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
			
			for(i = 0; i < indtri; i++) { //on parcours les mouvements tri�s
				if(nbdices == 0) {
					printf("Tous les d�s ont �t� utilis�s\n");
					nomove = 1;
					break;
				} else {
					requireddices = tempmoves[i].mouvement.dest_point-tempmoves[i].mouvement.src_point; //pas n�c�ssairement positif
					if(quatreMoves) {
						requireddices = requireddices/tirageDes[0];					//positif : nb d�s utilis�
						if(requireddices <= nbdices) {								//on v�rifie qu'on peut faire le move
							moves[movesdone] = tempmoves[i].mouvement;				//on ajoute le move
							movesdone++;											//on incr�mente le compte de move jou�s
							nbdices -= requireddices;								//on d�cr�mente les d�s encore non-utilis�s
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
						} else nbdices = 0;								//mettre le nbdices � 0 emp�che de reboucler, pas besoin de mettre � 0 les deux lancers
					}
				}
			}
		}
	}

}

/*
 - PRIORITE 1 : condition v�rifier si on a des pions de sortis et qu'il faut sortir en priorit� (TOP PRIORITE)
 - PRIORITE 2 : mouvement de pions tout seul sur leur case et qu'on peut s�curiser sur une pile		|  Par quart : de l'ennemi vers nous
 	-> si tous les pions adverses sont derriere, toujours securis�s
 - PRIORITE 3 : mouvement de deux pions sur des cases diff�rentes pouvant former une case s�curis�e
 - PRIORITE 4 : mouvement de pions pouvant bouffer un adversaire (et pouvant �tre s�curis� apr�s)	|  Resp. : de nous vers l'ennemi
 - PRIORITE 5 : cr�ation de case s�curis�e
 - PRIORITE 6 : mouvement s�curis�
 - PRIORITE 7 : mouvement d'un pion non s�curis� pour manger un adversaire							| d�pend peut-�tre du quart, � d�finir ensemble
 - PRIORITE 8 : mouvement non s�curis� d'un pion s�curis� pour manger un adversaire
 - PRIORITE 9 : sortir un pion vers le out
 - PRIORITE 10 : oups, sucks (mouvement par d�faut, en dernier recours)
 
 Qu'est-ce qu'on fait des priorit�s ? on fait des tableaux pour chaque priorit�s ? on trie par priorit� dans un m�me tableau ? on traite � l'arrache en parcourant les move � chaque fois ?
 
 	-> prioriser les mouvements des pions qui ne sont pas dans le dernier quart
 - on trouve les pions -> parcours des cases
 	-> pions de chaques joueurs (case, nb)
 - on liste tous nos mouvements
 	-> mouvements possibles, passages
 - on essaie de les regrouper
 	-> regarder si deux mouvements arrivent sur la m�me case
 - on mange les pions de l'adversaire delon leur position
 	-> proche de notre c�t�, on mange toujours, du c�t� adverse, seulement si on peut s�curiser nos pions
 - si on ne peut faire que des "mauvais" moves, on fait celui qui induit le moins de risque
 	-> pas de pions ennemis devant, ou trop loin, ou proche de notre c�t�
 	
 comparer l'�cart des d�s et celui des cases de pions -> ils peuvent donc arriver sur la m�me case !
 comparer les cases d'arriv�es et les cases des pions adverses -> les �liminer ou trouver des cases o� manger l'adversaire
 comparer les cases d'arriv�es et les cases des pions poss�d�s -> faire des mouvements "safe"
 comparer les mouvements restants par rapport aux positions adverses
 Trouver les cases o� on a qu'un seul pion, et essayer de les envoyer vers des cases d�j� poss�d�s ou les faire rejoindre par un autre pion
*/