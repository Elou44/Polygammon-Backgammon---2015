# Polygammon-Backgammon---2015
# PS : Windows c'est de la merde !! (Ambre dira pas le contraire)
Project realised by engineering students of Polytech'Nantes (French engineering school)

Voilà , il est temps de s'y mettre ! 

## Récapitulatif des tâches : 

#### Groupe IA : Freddy & Varou 
- les deux zozos sur l'IA


#### Groupe IHM & Arbitre : Elou, Ambre & Oliver
- Elou & Oliver : Graphisme et interface
- Ambre : Arbitre

## Compilation :
export LD_LIBRARY_PATH=. (ajouter le répertoire courant pour chercher les librairies)
- gcc -o PolygammonLinux main.c \`sdl-config --cflags --libs\` -ldl  (sous Linux)
- compiler seulement avec CodeBlocks (une fois paramétré) 
- (pour obtenir le caractère " ` " taper ALTGR + 7 (PAS celui du pavé numérique) puis ESPACE)

## Paramétrage de CodeBlocks :
vous pouvez coder sur CodeBlocks (sous Windows)  mais pour que ça marche, il faut d'abord configurer votre CodeBlocks
Suivez les instructions suivantes :
 The Process

- Download SDL-devel-1.2.9-mingw32.tar.gz from the SDL version 1.2.9 download page. There are binary packages for several Linux distributions, too (rpm may have problems downloading directly from libsdl.org, use wget to get the packages in that case).
- Decompress the archive
- Copy SDL.dll from inside the bin folder to the your compilers bin directory (ie C:\Mingw\bin) This allows the compiler to find the dll at runtime time without having to put it in the same folder as your program or in the windows folder.
- Copy the contents of lib to your compiler's lib folder. If MinGW is installed under C:\MinGW, then this will be C:\MinGW\lib.
- Copy the complete folder SDL from inside the folder include to your compiler's include directory (for example C:\MinGW\include). Be sure to copy the folder, not the individual files.
- Optionally, copy SDL.dll to C:\Windows, too. This will save you from copying the dll to each and every project directory while developing. Be cautious, however, not to find yourself in DLL hell afterwards.


### Commandes Git: ###

Site pour configurer Git Bash : http://blog.hfarazm.com/git-for-unity-create-projects/
Ou : http://openclassrooms.com/courses/gerez-vos-codes-source-avec-git (voir dans "cloner dépôt" si jamais on a reset son PC et qu'on est plus connecté au dépôt)

* git pull
* git add . 
* git commit -m "commentaire" . 
* git push 

Pour ceux qui ont une ancienne version de Git Bash : git config --global push.default simple



// STATIC LIB //

SOUS LINUX :

gcc -c main.c
gcc -c libXXX.c
ar -q libXXX.a libXXX.o
gcc -o main main.c libXXX.a
./main


SOUS WINDOWS :

gcc -c main.c
gcc -c libXXX.c
ar -q libXXX.lib libXXX.o
gcc -o main main.c libXXX.lib
main




// DYNAMIc LIB //

SOUS LINUX :

gcc -c main.c
gcc -c libXXX.c
gcc -o libXXX.so -shared libXXX.o
gcc -o main main.o libXXX.so
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH // on rajoute une variable d'environnement , ici le dossier courant
./main


SOUS WINDOWS :

gcc -c main.c
gcc -c libXXX.c
gccgcc -o  -o libXXX.dll -shared libXXX.o
gcc -o main main.o libXXX.dll
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH // on rajoute une variable d'environnement , ici le dossier courant
main



http://www.trustonme.net/didactels/154.html

### Installation de SDL2 sur CodeBlocks :
- téléchargez SDL2-devel-2.0.3-mingw.tar.gz (MinGW 32/64-bit) sur https://www.libsdl.org/download-2.0.php
- décompressez l'archive. le dossier que vous allez utiliser est : i686-w64-mingw32 (IMPORTANT)
- collez SDL2.dll situé dans bin dans le bin de CodeBlocks (C:/ProgamFiles/CodeBlocks/MinGW/bin)
- collez le DOSSIER SDL2 (situé dans include) dans le dossier include de CodeBlocks
- collez les fichiers situé dans lib dans le dossier lib de CodeBlocks

Normalement ça devrait etre bon ! 

### Installation de SDL_ttf sur CodeBlocks :
- téléchargez SDL2_ttf-devel-2.0.12-VC.zip sur https://www.libsdl.org/projects/SDL_ttf/
- décompressez l'archive. 
- collez SDL_ttf.h situé dans include dans le include/SDL2 de CodeBlocks (C:/ProgamFiles/CodeBlocks/MinGW/include/SDL2)
- collez les lib (dossier lib/x86) dans le dossier lib de CodeBlocks

Normalement ça devrait etre bon ! 
