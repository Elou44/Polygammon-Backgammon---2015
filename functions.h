#include <SDL2/SDL.h>
// DECLARATION DES POINTEURS DE FONCTIONS DE L'API //

typedef struct {
    SDL_Rect *rectHB;
} Hitbox;


typedef struct {
    unsigned int color; // 0 blanche 1 noire
    SDL_Rect *rectDame; // position de l'image
} Dame;

// Les diff�rents �tats de jeu
typedef enum {
    SINITLIBS, // initialisation des librairies
    SSTARTMATCH, // d�marrage du match
    SSTARTGAME, // d�marrage de la game
    SROLLDICES, // lanc� de d�s
    SPLAY, // mouvements de l'IA
    SDOUBLETAKEN, // si le double est pris par le joueur
    SENDGAME,
    SENDMATCH

} States;

// les diff�rents mode de jeu
typedef enum {
    MHvsH, // humain contre humain
    MHvsAI, // humain contre IA
    MAIvsAI // IA contre IA
} GameMode;

/**
 * @brief D�finit quel joueur contr�le la case.
 *
 * Les nombres sont l� pour faciliter les tests.
 */
typedef enum {
    BLACK = 0,
    NOBODY = -1,
    WHITE = 1
} Player;

/**
 * @brief D�finit le contenu d'une case de jeu.
 */
typedef struct {
    Player owner;           /*!<  Joueur contr�lant la case */
    unsigned int nbDames;   /*!<  Nombre de dames sur la case (non utilis� si
                                  `owner == NOBODY.`) */
} Square;


/**
 * @brief Contient toutes les informations relatives � une partie en cours.
 *
 * Une struct contenant toutes les informations du jeu permet des tests plus
 * faciles.
 */
typedef struct {
    Square board[24];           /*!< Les 24 cases du tableau, en partant du bord blanc. */
	unsigned int bar[2];
	unsigned int out[2];
    unsigned int whiteScore;    /*!< Score du joueur blanc */
    unsigned int blackScore;    /*!< Score du joueur noir */
    unsigned int turn;          /*!< Num�ro du tour en cours (initialis� � 0) */
	unsigned int stake;			/*!< Mise courante de la partie */
} SGameState;

// Structure de repr�sentation d'un mouvement
typedef struct
{
	unsigned int src_point;
	unsigned int dest_point;
} SMove;

/////////// Fonctions � utiliser
// Les prototypes en commentaires sont � impl�menter dans la librairie
// Les types pointeur de fonction dans l'application

/**
 * Initialiser la librairie
 * @param char name[50]
 *	nom associ� � la librairie
 */
//void InitLibrary(char name[50]);
typedef void (*pfInitLibrary)(char[50]);

/**
 * Initialiser l'IA pour un match
 * @param const unsigned int target_score
 *	score cible pour gagner un match
 */
//void StartMatch(const unsigned int target_score);
typedef void (*pfStartMatch)(const unsigned int);

/**
 * Initialiser l'IA pour une manche (d'un match)
 */
//void StartGame(Player p);
typedef void (*pfStartGame)(Player);

/**
 * Fin d'une manche (d'un match)
 */
//void EndGame();
typedef void (*pfEndGame)();

/**
 * Fin d'un match
 */
//void EndMatch();
typedef void (*pfEndMatch)();

/**
 * Doubler la mise
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @return int
 *	vrai si on propose de doubler : faux sinon
 */
//int DoubleStack(const SGameState * const gameState);
typedef int (*pfDoubleStack)(const SGameState * const);

/**
 * Accepter ou refuser la nouvelle mise
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @return int
 *	vrai si on accepte la nouvelle mise ; faux sinon
 */
//int TakeDouble(const SGameState * const gameState);
typedef int (*pfTakeDouble)(const SGameState * const);

/**
 * Prise de d�cision de la part de l'IA.
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @param SMove moves[4]
 *	tableau des mouvements � effectuer par l'IA
 * @param unsigned int tries
 *	nombre d'essais restants (3 initialement).
 */
//void PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries);
typedef void (*pfPlayTurn)(const SGameState * const,  const unsigned char[2], SMove[4], unsigned int*, unsigned int);


/**
 * Calcule le score de chaque joueur.
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 */
void setScore(SGameState* gamestate);

void setScore2(SGameState* gamestate);

/**
 * Fonction utilis�e dans setDamesPos. Met la bonne SDL_surface � chaque Dame (pion).
 * @param int i
 *	indice du board
 * @param int z
 *	indice de la Dame dans le tableau damesTab
 * @param Dame *damesTab
 *	tableau de Dames (pions)
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @param SDL_Surface dameWsurf
 *	surface des pions blanc
 * @param SDL_Surface dameBsurf
 *	surface des pions noir
 */
void setSurf(int i, int z, Dame *damesTab, const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf);


/**
 * Place les pions sur le plateau de jeu en fonction d'un SGameState donn�.
 * @param Dame *damesTab
 *	tableau de Dames (pions)
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 * @param SDL_Surface dameWsurf
 *	surface des pions blanc
 * @param SDL_Surface dameBsurf
 *	surface des pions noir
 */
void setDamesPos(Dame *damesTab, const SGameState* const gamestate, SDL_Surface *dameWsurf, SDL_Surface *dameBsurf);


/**
 * Initialisation de l'�tat de jeu (configuration d�but de partie).
 * @param const SGameState * const gameState
 *	l'�tat du jeu courant
 */
void initGameState(SGameState* gamestate);


/**
 * Dessine les Dames (pions) sur l'�cran
 * @param Dame *damesTab
 *	tableau de Dames (pions)
 * @param SDL_Surface* screen
 *	surface de l'�cran
 * @param int nbDames
 *	nombre de Dames
 */
void drawDames(Dame *damesTab,SDL_Surface* dameWsurf, SDL_Surface* dameBsurf, SDL_Surface* screen, int nbDames);

/**
 * Initialisation du tableau des Dames (Allocations dynamiques de m�moires)
 * @param Dame *damesTab
 *	tableau de Dames (pions)
 * @param int nbDames
 *	nombre de Dames
 */
void initDamesTab(Dame *damesTab, int nbDames);

/**
 * Initialisation du tableau des hitboxes (Allocations dynamiques de m�moires)
 * @param Hitbox *hitboxesTab
 *	tableau de Hitbox
 * @param int nbHB
 *	nombre de Hitbox
 * @param SDL_Surface* screen (DEBUG purpose)
 *	surface de l'�cran (pour dessiner les hitboxes � l'�cran)
 */
void initHitBoxesTab(Hitbox *hitboxesTab, int nbHB, SDL_Surface* screen);

/**
 * Renvoie l'indice de la hitbox cliqu�e (ou -1 si aucune hitbox n'est cliqu�e)
 * @param Hitbox *hitboxesTab
 *	tableau de Hitbox
 * @param int nbHB
 *	nombre de Hitbox
 * @param int x
 *	abscisse du pointeur de la souris
 * @param int y
 *	ordonn�e du pointeur de la souris
 */
int detectClickIntoHitbox(Hitbox *hitboxesTab, int nbHB, int x, int y);

/**
 * Tire deux d�s al�atoirement
 * @param unsigned char* dices
 *	tableau de caract�res (repr�sentant les d�s tir�s)
 */
void rollDices(unsigned char* dices);

void updateSGameState(SGameState* gamestate, SMove* moves, unsigned int *nbMoves, Player curPlayer);

void clickToSMoves(int* indiceHBTab, SMove* moves,unsigned int *nbMoves);





