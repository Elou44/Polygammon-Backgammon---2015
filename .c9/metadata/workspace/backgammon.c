{"changed":true,"filter":false,"title":"backgammon.c","tooltip":"/backgammon.c","value":"#include \"backgammon.h\"\n#include <stdio.h>\n#include <string.h>\n\n//////////////////////////////////////////////////////////\n// Dans la librairie\n//\n\n// Apparemment il faut faire une structure globale pour stocker toutes les infos dont on a besoin pour implémenter nos fonctions\n\ntypedef struct {\t// Structure d'une IA, regroupant les infos dont on a besoin pour les fonctions et la stratégie\n\tchar nom[50];\t\t\t\t\t// Nom de l'IA\n\tunsigned int couleur;\t\t\t// Couleur des pions de l'IA\n\tunsigned int scoreActuel[2];\t// Nombre de manches gagnées\n\tunsigned int scorePourGagner;\t// Nombre de manches nécessaires pour gagner un match\n\tunsigned int scoreManche;\t\t// Score de la manche (selon l'emplacement des pions genre l'addition du nombre des cases)\n\tunsigned int pions;\t\t\t\t// Nombre de pions encore sur le plateau\n\tint mancheActuelle;\t\t\t\t// Numéro de la manche jouée actuellement\n\tunsigned int resultatMatch;\t\t// 1 si cette IA a gagnée, 0 sinon\n}IA;\n\n// Sinon on peut aussi regrouper cette structure avec IA\ntypedef struct {\t// Structure décrivant les mouvements possibles à partir d'une case de départ (3 moves max)\n\tint directMove[2];\t\t\t\t// Numéros de cases accessibles en un mouvement\n\tint longMove[3];\t\t\t\t// Numéros de cases accessibles en plusieurs mouvements\n}Mouvements;\n\ntypedef struct {\n\tint indice;\t\t\t\t\t\t// Numéro de la case\n\tSquare sq;\t\t\t\t\t\t// Structure Square de la case\n\tMouvements moves;\t\t\t\t// Structure Mouvements de la case\n}Carre;\n\nIA OliverJohn;\n\nvoid InitLibrary(char name[50])\n{\n\tprintf(\"Initiating library...\\n\");\n\tstrcopy();\n}\n\nvoid StartMatch(const unsigned int target_score)\n{\n\tprintf(\"Starting match...\\n\");\n\t/* En paramètres le nombre de Game à gagner pour remporter le match\n\tInitialiser l'IA pour un match\n\tInitialisation du nombre de manches à gagner dans la structure\n\tInitialisation à 0 du nombre de manches actuelles gagnées\n\t*/\n\n\tOliverJohn->scoreActuel = 0;\n\tOliverJohn->scorePourGagner = target_score;\n\tOliverJohn->mancheActuelle = -1;\n\tOliverJohn->resultatMatch = 0;\n}\n\nvoid StartGame(Player p)\n{\n\tprintf(\"StartGame\\n\");\n\t/* En paramètre l'énumération Player disant à qui appartient la case\n\tInitialiser l'IA pour une manche\n\tInitialisation du score de la manche à 0\n\t*/\n\n\tOliverJohn->scoreManche = 0;\n\tOliverJohn->mancheActuelle++;\n}\n\nvoid EndGame()\t// On indique juste que la manche est terminée, vu qu'on renvoie rien\n/* Mais au final je sais pas si on doit afficher un truc, plutôt l'interface graphique\n pour qu'ils le fassent tout beau et tout, on verra pas la console sinon */\n{\n\tprintf(\"EndGame\\n\");\n\tprintf(\"Manche terminée\\n\");\n\tprintf(\"Score actuel : %s -> %d points\\n\", OliverJohn->nom, OliverJohn->scoreActuel);\n}\n\nvoid EndMatch()\t// On indique juste que le match est terminé\n// Même chose ici, en fait je pense pas qu'on doive print un truc\n// \n{\n\tprintf(\"EndMatch\\n\");\n\tprintf(\"Partie terminée\\n\");\n\tprintf(\"IA %s avec un score de %d\\n\", OliverJohn->nom, OliverJohn->scoreActuel);\n}\n\nint DoubleStack(const SGameState * const gameState)\n{\n\tprintf(\"DoubleStack\\n\");\n\treturn(0);\n}\n\nint TakeDouble(const SGameState * const gameState)\n{\n\tprintf(\"TakeDouble\\n\");\n\treturn(0);\n}\n\nvoid PlayTurn(const SGameState * const gameState, const unsigned char dices[2], SMove moves[4], unsigned int *nbMove, unsigned int tries)\n{\n\n\t/*\n\t#############################################\n\t######### Déclaration des variables #########\n\t#############################################\n\t*/\n\n\tCarre casesAllies[15];\t\t\t// Tableau des cases qui nous appartiennent\n\tCarre casesEnnemies[15];\t\t// Tableau des cases ennemis\n\tSMove mouvts[60];\n\tint i, quatreMoves = 0;\t\t\t// Indice de parcours de boucle\n\tint j = 0, k = 0;\t\t\t\t// Indices pour remplir les tableaux des cases, respectivement Alliées / Ennemies\n\n\tprintf(\"Début du tour\\n\");\n\t\n\tif(OliverJohn->couleur == 0) {\n\t\tdices[0] = -dices[0];\n\t\tdices[1] = -dices[1];\n\t}\n\n\t/*\n\t#############################################\n\t#Remplissage tableaux cases Alliées/Ennemies#\n\t#############################################\n\t*/\n\n\t// Parcours de chaque case du plateau pour repérer les cases à nous ou pas -> Remplissage des tableaux appartenance des cases\n\tfor (i = 0; i < len(gameState->board); i++)\n\t{\n\t\tif (gameState->board[i]->owner == OliverJohn->couleur)\t// Si le proprio de la case (enum Player) est égal à notre couleur\n\t\t{\n\t\t\tcasesAllies[j]->indice = i;\t// Juste avant de garder la structure Square, on garde le numéro de la case (pour les mouvements)\n\t\t\tcasesAllies[j]->sq = gameState->board[i];\t// On garde une structure Square donnant le nombre de Dames présentes sur la case \n\t\t\tj++;\t// On incrémente l'indice de remplissage des cases alliées dès qu'on a remplit la case d'avant\n\t\t}\n\t\telse\n\t\t{\n\t\t\tcasesEnnemies[k]->indice = i;\n\t\t\tcasesEnnemies[k]->sq = gameState->board[i];\n\t\t\tk++;\t// On incrémente l'indice de remplissage des cases ennemies dès qu'on a remplit la case d'avant\n\t\t}\n\t}\n\n\t/*\n\t#############################################\n\t##### Listing des mouvements possibles ######\n\t#############################################\n\t*/\n\n\t// Boucle de remplissement de la structure casesAllies\n\tk = 0;\n\tfor (j = 0; j < len(casesAllies); j++)\n\t{\n\t\tif(dices[0] == dices[1]) {\n\t\t\t//On peut regarder directement si la case est occupé par au moins 2 ennemis\n\t\t\tquatreMoves = 1;\n\t\t\t\n\t\t\tif(gameState->board[j+dices[0]->owner != OliverJohn->couleur && gameState->board[j+dices[0]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->directMove[0] = -1;\n\t\t\t} else {\n\t\t\t\tcasesAllies[j]->moves->directMove[0] = j+dices[0];\n\t\t\t\tmouvts[k]->src_point = j; mouvts[k]->dest_point = j\n\t\t\t}\n\t\t\t\n\t\t\tcasesAllies[j]->moves->directMove[1] = -1;\n\t\t\t\n\t\t\tif(gameState->board[j+2*dices[0]->owner != OliverJohn->couleur && gameState->board[j+2*dices[0]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->longMove[0] = -1;\n\t\t\t} else casesAllies[j]->moves->longMove[0] = j+2*dices[0];\n\t\t\t\n\t\t\tif(gameState->board[j+3*dices[0]->owner != OliverJohn->couleur && gameState->board[j+3*dices[0]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->longMove[1] = -1;\n\t\t\t} else casesAllies[j]->moves->longMove[1] = j+3*dices[0];\n\t\t\t\n\t\t\tif(gameState->board[j+4*dices[0]->owner != OliverJohn->couleur && gameState->board[j+4*dices[0]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->longMove[2] = -1;\n\t\t\t} else casesAllies[j]->moves->longMove[2] = j+4*dices[0];\n\t\t\t\n\t\t\t\n\t\t} else {\n\t\t\t\n\t\t\tif(gameState->board[j+dices[0]->owner != OliverJohn->couleur && gameState->board[j+dices[0]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->directMove[0] = -1;\n\t\t\t} else casesAllies[j]->moves->directMove[0] = j+dices[0];\n\t\t\t\n\t\t\tif(gameState->board[j+dices[1]->owner != OliverJohn->couleur && gameState->board[j+dices[1]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->directMove[1] = -1;\n\t\t\t} else casesAllies[j]->moves->directMove[1] = j+dices[1];\n\t\t\t\n\t\t\tif(gameState->board[j+dices[0]+dices[1]->owner != OliverJohn->couleur && gameState->board[j+dices[0]+dices[1]->nbDames > 1) {\n\t\t\t\tcasesAllies[j]->moves->longMove[0] = -1;\n\t\t\t} else casesAllies[j]->moves->longMove[0] = j+dices[0]+dices[1];\n\t\t\t\n\t\t\tcasesAllies[j]->moves->longMove[1] = -1;\n\t\t\tcasesAllies[j]->moves->longMove[2] = -1;\n\t\t}\n\t}\n\n\t/*\n\t#############################################\n\t########## Choix des moves à faire ##########\n\t#############################################\n\t*/\n\t\n\tint nbdices = 0, nomove = 0;\n\tif(quatreMoves) {\n\t\tnbdices = 4;\n\t} else nbdices = 2;\n\t\n\twhile(nbdices || nomove) {\n\t\tnomove = 1;\n\t\tfor(i = 0; i < len(casesAllies); i++)\n\t\t{\n\t\t\tif(casesAllies[i]->move->directMove[0] != -1 || casesAllies[i]->move->directMove[1] != -1 || casesAllies[i]->move->longMove[0] != -1\n\t\t\t|| casesAllies[i]->move->longMove[1] != -1 || casesAllies[i]->move->longMove[2] != -1) {\n\t\t\t\tnomove = 0;\n\t\t\t} \n\t\t}\n\t}\n\n}\n\n/*\n - on trouve les pions -> parcours des cases\n \t-> pions de chaques joueurs (case, nb)\n - on liste tous nos mouvements\n \t-> mouvements possibles, passages\n - on essaie de les regrouper\n \t-> regarder si deux mouvements arrivent sur la même case\n - on mange les pions de l'adversaire delon leur position\n \t-> proche de notre côté, on mange toujours, du côté adverse, seulement si on peut sécuriser nos pions\n - si on ne peut faire que des \"mauvais\" moves, on fait celui qui induit le moins de risque\n \t-> pas de pions ennemis devant, ou trop loin, ou proche de notre côté\n \t\n comparer l'écart des dés et celui des cases de pions -> ils peuvent donc arriver sur la même case !\n comparer les cases d'arrivées et les cases des pions adverses -> les éliminer ou trouver des cases où manger l'adversaire\n comparer les cases d'arrivées et les cases des pions possédés -> faire des mouvements \"safe\"\n comparer les mouvements restants par rapport aux positions adverses\n Trouver les cases où on a qu'un seul pion, et essayer de les envoyer vers des cases déjà possédés ou les faire rejoindre par un autre pion\n*/","undoManager":{"mark":-1183,"position":100,"stack":[[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"remove","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":9},"end":{"row":109,"column":10},"action":"remove","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":8},"end":{"row":109,"column":9},"action":"remove","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":7},"end":{"row":109,"column":8},"action":"remove","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":7},"end":{"row":109,"column":8},"action":"insert","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":8},"end":{"row":109,"column":9},"action":"insert","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":9},"end":{"row":109,"column":10},"action":"insert","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":12},"end":{"row":109,"column":13},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":13},"end":{"row":109,"column":14},"action":"insert","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":14},"end":{"row":109,"column":15},"action":"insert","lines":["f"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":15},"end":{"row":109,"column":16},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":16},"end":{"row":109,"column":17},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":17},"end":{"row":109,"column":18},"action":"insert","lines":["g"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":17},"end":{"row":109,"column":18},"action":"remove","lines":["g"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":16},"end":{"row":109,"column":17},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":15},"end":{"row":109,"column":16},"action":"remove","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":14},"end":{"row":109,"column":15},"action":"remove","lines":["f"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":13},"end":{"row":109,"column":14},"action":"remove","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":12},"end":{"row":109,"column":13},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"remove","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":9},"end":{"row":109,"column":10},"action":"remove","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":8},"end":{"row":109,"column":9},"action":"remove","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":7},"end":{"row":109,"column":8},"action":"remove","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":7},"end":{"row":109,"column":8},"action":"insert","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":8},"end":{"row":109,"column":9},"action":"insert","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":9},"end":{"row":109,"column":10},"action":"insert","lines":["u"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":12},"end":{"row":109,"column":13},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":13},"end":{"row":109,"column":15},"action":"insert","lines":["[]"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":14},"end":{"row":109,"column":15},"action":"insert","lines":["6"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":15},"end":{"row":109,"column":16},"action":"insert","lines":["0"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":17},"end":{"row":109,"column":18},"action":"insert","lines":[";"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":12},"end":{"row":109,"column":13},"action":"remove","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"remove","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":10},"end":{"row":109,"column":11},"action":"insert","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":12},"end":{"row":109,"column":13},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"remove","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":109,"column":11},"end":{"row":109,"column":12},"action":"insert","lines":["t"]}]}],[{"group":"doc","deltas":[{"start":{"row":158,"column":9},"end":{"row":158,"column":10},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":158,"column":10},"end":{"row":158,"column":11},"action":"insert","lines":["{"]}]}],[{"group":"doc","deltas":[{"start":{"row":158,"column":11},"end":{"row":158,"column":12},"action":"remove","lines":[" "]},{"start":{"row":158,"column":11},"end":{"row":159,"column":0},"action":"insert","lines":["",""]},{"start":{"row":159,"column":0},"end":{"row":159,"column":4},"action":"insert","lines":["\t\t\t\t"]}]}],[{"group":"doc","deltas":[{"start":{"row":159,"column":54},"end":{"row":160,"column":0},"action":"insert","lines":["",""]},{"start":{"row":160,"column":0},"end":{"row":160,"column":4},"action":"insert","lines":["\t\t\t\t"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":4},"end":{"row":161,"column":0},"action":"insert","lines":["",""]},{"start":{"row":161,"column":0},"end":{"row":161,"column":4},"action":"insert","lines":["\t\t\t\t"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":4},"end":{"row":161,"column":5},"action":"insert","lines":["}"]},{"start":{"row":161,"column":0},"end":{"row":161,"column":4},"action":"remove","lines":["\t\t\t\t"]},{"start":{"row":161,"column":0},"end":{"row":161,"column":3},"action":"insert","lines":["\t\t\t"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":4},"end":{"row":160,"column":5},"action":"insert","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":5},"end":{"row":160,"column":6},"action":"insert","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":6},"end":{"row":160,"column":7},"action":"insert","lines":["u"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":7},"end":{"row":160,"column":8},"action":"insert","lines":["v"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":8},"end":{"row":160,"column":9},"action":"insert","lines":["t"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":9},"end":{"row":160,"column":10},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":160,"column":10},"end":{"row":160,"column":12},"action":"insert","lines":["[]"]}]}],[{"group":"doc","deltas":[{"start":{"row":149,"column":55},"end":{"row":150,"column":0},"action":"insert","lines":["",""]},{"start":{"row":150,"column":0},"end":{"row":150,"column":1},"action":"insert","lines":["\t"]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":1},"end":{"row":150,"column":2},"action":"insert","lines":["k"]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":2},"end":{"row":150,"column":3},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":3},"end":{"row":150,"column":4},"action":"insert","lines":["="]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":4},"end":{"row":150,"column":5},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":5},"end":{"row":150,"column":6},"action":"insert","lines":["0"]}]}],[{"group":"doc","deltas":[{"start":{"row":150,"column":6},"end":{"row":150,"column":7},"action":"insert","lines":[";"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":11},"end":{"row":161,"column":12},"action":"insert","lines":["k"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":13},"end":{"row":161,"column":14},"action":"insert","lines":["-"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":14},"end":{"row":161,"column":15},"action":"insert","lines":[">"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":16},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":16},"action":"remove","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":16},"action":"insert","lines":["d"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":16},"action":"remove","lines":["d"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":16},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":16},"end":{"row":161,"column":17},"action":"insert","lines":["r"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":17},"end":{"row":161,"column":18},"action":"insert","lines":["c"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":15},"end":{"row":161,"column":18},"action":"remove","lines":["src"]},{"start":{"row":161,"column":15},"end":{"row":161,"column":24},"action":"insert","lines":["src_point"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":24},"end":{"row":161,"column":25},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":25},"end":{"row":161,"column":26},"action":"insert","lines":["="]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":26},"end":{"row":161,"column":27},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":27},"end":{"row":161,"column":28},"action":"insert","lines":["j"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":28},"end":{"row":161,"column":29},"action":"insert","lines":[";"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":29},"end":{"row":161,"column":30},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":30},"end":{"row":161,"column":31},"action":"insert","lines":["m"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":31},"end":{"row":161,"column":32},"action":"insert","lines":["o"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":32},"end":{"row":161,"column":33},"action":"insert","lines":["u"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":30},"end":{"row":161,"column":33},"action":"remove","lines":["mou"]},{"start":{"row":161,"column":30},"end":{"row":161,"column":36},"action":"insert","lines":["mouvts"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":36},"end":{"row":161,"column":38},"action":"insert","lines":["[]"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":37},"end":{"row":161,"column":38},"action":"insert","lines":["k"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":39},"end":{"row":161,"column":40},"action":"insert","lines":["-"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":40},"end":{"row":161,"column":41},"action":"insert","lines":[">"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":41},"end":{"row":161,"column":42},"action":"insert","lines":["d"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":42},"end":{"row":161,"column":43},"action":"insert","lines":["e"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":43},"end":{"row":161,"column":44},"action":"insert","lines":["s"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":41},"end":{"row":161,"column":44},"action":"remove","lines":["des"]},{"start":{"row":161,"column":41},"end":{"row":161,"column":51},"action":"insert","lines":["dest_point"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":51},"end":{"row":161,"column":52},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":52},"end":{"row":161,"column":53},"action":"insert","lines":["="]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":53},"end":{"row":161,"column":54},"action":"insert","lines":[" "]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":54},"end":{"row":161,"column":55},"action":"insert","lines":["j"]}]}],[{"group":"doc","deltas":[{"start":{"row":161,"column":54},"end":{"row":161,"column":55},"action":"remove","lines":["j"]},{"start":{"row":161,"column":54},"end":{"row":161,"column":55},"action":"insert","lines":["j"]}]}]]},"ace":{"folds":[],"scrolltop":2222.5,"scrollleft":0,"selection":{"start":{"row":161,"column":55},"end":{"row":161,"column":55},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":147,"state":"start","mode":"ace/mode/c_cpp"}},"timestamp":1427804486542}