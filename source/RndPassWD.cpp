/*
  Name: rndPassWD.cpp
  Copyright: Luc Paul Labonté
  Author: Luc Paul Labonté
  Date: 21-01-06 14:38
  Description: générer des mot de passes aléatoirement

  Modifié le 24-06-2010.
  Ajout de la définition WIN32 pour windows, avoir le temps
  (Sleep) fonctionne pour windows. Also a print version system
  and copyright updated.

  Modifié le 20-12-2013.
  * Changement du nom de la source.
  * Fichier source UTF-8.
  * Amélioration de l'utilisation des paramètres.
  * Optimisation de l'affichage des passwords.
  * Mise à jour du message d'erreur des parametres.
  * Copyright updated.
*/

#define _WIN32_	// Activate only if on windows

#define VER "3.0"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;


struct PARAM{
	bool lower;
	bool upper;
	bool number;
	bool charac;
	int nbChars;
	int genTime;
	int secWait;
	char* progName;
};

void printArgsUsed( PARAM* param ) {
	cout << "Arguments used: " << endl
		  << "  Number of chars -> " << param->nbChars << endl
		  << "  Upper cases     -> "; param->upper == true ? cout << "YES": cout << "NO";
	 cout << endl;
	 cout << "  Lower cases     -> "; param->lower == true ? cout << "YES": cout << "NO";
	 cout << endl;
	 cout << "  Numbers         -> "; param->number == true ? cout << "YES": cout << "NO";
	 cout << endl;
	 cout << "  Specials chars  -> "; param->charac == true ? cout << "YES": cout << "NO";
	 cout << endl
		  << "  PWD generated   -> " << param->genTime << endl
		  << "  Time to sleep   -> " << param->secWait << endl << endl
		  << "Generating password"; param->genTime > 1? cout << "s":cout <<"";
}

//********************************************************************
// Nom de la procédure: GESTION_ERREUR
// Description        : Gère les erreures d'entrée de paramètre
// Entrés             : zeFuck
// Sorties            : none
// Retour             : 0
//********************************************************************
int GESTION_ERREUR( bool error = false, PARAM* p = NULL )
{
      //cout << ZeFuck << "\n\n\t";

	if( error == true ) {
		cout << endl << "\t\t *** ARGUMENTS ERROR!!! ***" << endl;
		//if( p != NULL ) {
			//printArgsUsed(p);
		//}
	} else {
		cout << endl << "\t\t *** ARGUMENTS HELP :D ***" << endl;
	}

      cout << endl << "  The correct syntax is: " << endl
           << endl << "    rndPassWD [options]" << endl
           << endl << "options:" << endl
           << "  -n {number}    The number of characters to generate for the current password." << endl
           << "                 The default value is 6. Must be greater than 1." << endl
	       << "  -c [chars]     The types of characters to use." << endl
	       << "    chars:" << endl
	       << "      l    Lower case characters. [a-z]*" << endl
	       << "      u    Upper case characters.[A-Z]*" << endl
	       << "      n    Number characters. [0-9]*" << endl
	       << "      a    Any characters. e.g.: !@#$%?&*().',\"|" << endl
	       << "  -g {number}    The number of passwords to generage. The default value is 1." << endl
	       << "                 Must be greater than 0." << endl
	       << "  -w {sec}       The time in seconds elapsed between generation of passwords." << endl
	       << "                 Help prevent duplicate passwords. Default value is 1. The time" << endl
	       << "                 is in seconds. Must be greater than 0." << endl
	       << "  -?, h          Print this help message" << endl
           << endl << "Version: " << VER << endl;
      cout << "Luc Paul Labonté (c)2006-2014" << endl << endl;

      exit(1);
	return 0;
}



//********************************************************************
// Nom de la procédure: aleatoire
// Description        : génère les caractères aléatoires
// Entrés             : nbCaracteres, maj, min, chi, carac
// Sorties            : none
// Retour             : 0
//********************************************************************
int aleatoire( int nbCaracteres, bool maj, bool min, bool chi,
	      			bool carac, int zeLoop, int secSleep )
{
    int temps = 0;
    int compteurChar = 0;
    int j;

    char passWD[nbCaracteres + 1];	// To insert NULL char


    if( secSleep < 1 )
    {
		cout << endl<<endl<<"Sleep time must be >= 1." << endl;
		cout << "We will use 1 for now!" << endl;
		secSleep = 1;
    }

    cout << endl << "New Password: " << endl;

    for( j = 0; j < zeLoop; j++ )
    {
#ifdef _WIN32_
    	Sleep( secSleep * 1000 );
#else
    	sleep( secSleep );
#endif
    	compteurChar = 0;
    	srand( time(NULL));

    	try{
    		while( compteurChar < nbCaracteres )
    		{
	     		temps = rand()%4;
	    	   	// Les Chiffres
		   	if( chi == true )
		   	{
		    	 	if( temps == 0 )
		    	 	{
	    		     		passWD[compteurChar] = rand()%10 + 48;
			     		compteurChar++;
	    		 	}
		   	}
		   	// Les caracteres ASCII
		   	if( carac == true )
		   	{
		    	 	if( temps == 1 )
			 	{
	   		     		passWD[compteurChar] = rand()%14 + 33;
	   		     		compteurChar++;
	             		}
	         	}
	         	// Les majuscules
	         	if( maj == true )
	         	{
		    	 	if( temps == 2 )
	   		 	{
			 		passWD[compteurChar] = rand()%26 + 65;
			 		compteurChar++;
			 	}
	         	}
	         	// Les minuscules
		   	if( min == true )
	         	{
		    	 	if( temps == 3 )
	    		 	{
		    	 		passWD[compteurChar] = rand()%26 + 97;
						compteurChar++;
	    		 	}
	         	}

     	 	}

			passWD[compteurChar] = '\0';
			cout << passWD;
	     	cout << endl;

		}
    	catch( char fuck )
    	{
     		GESTION_ERREUR( true );
    	}

    }

    	cout << endl << endl <<"Merci d'avoir utiliser rndPassWD2 :)" << endl
	     << "Programmé par: Luc paul Labonté" << endl
	     << "CopyRight 2006-2014 Luc Paul Labonté (c)2006-2014" << endl << endl;

    return 0;
}// fin de la procedure

void charArgument(char* arg, PARAM* p) {
	int j = 0;
	if( strlen(arg) <= 0 ) {
		GESTION_ERREUR(true, p);
	}
	while(arg[j] != '\0') {
		switch(arg[j]) {
			case 'l':
				p->lower = true;
			break;
			case 'u':
				p->upper = true;
			break;
			case 'n':
				p->number = true;
			break;
			case 'a':
				p->charac = true;
			break;
			default:
				GESTION_ERREUR(true, p);
			break;
		}
		++j;
	}
}

PARAM* parseArgs( int argc, char** argv )
{
	PARAM* param = (PARAM*) malloc( sizeof(PARAM) );

	param->charac = false;
	param->genTime = 1;
	param->lower = true;
	param->nbChars = 6;
	param->number = false;
	param->secWait = 1;
	param->upper = false;
	param->progName = argv[0];

	for( int i = 1; i < argc; i++ )
	{
		// check args, skip '-' char
		switch(argv[i][1]) {

			case 'n':
				++i;
				param->nbChars = atoi(argv[i]);
			break;

			case 'c':
				++i;
				charArgument(argv[i], param);
			break;

			case 'w':
				++i;
				param->secWait = atoi(argv[i]);
			break;

			case 'g':
				++i;
				param->genTime = atoi(argv[i]);
			break;

			case '?':
			case 'h':
				GESTION_ERREUR();
			break;

			default:
				GESTION_ERREUR(true, param);
			break;
		}
	}

	return param;
}

//********************************************************************
// Nom de la procédure: gerer
// Description        : Gérer les paramètres
// Entrés             : param
// Sorties            : param
// Retour             : 0
//********************************************************************
int gerer( PARAM* param )
{

	printArgsUsed(param);
	 cout<< ", please wait..." << endl;

     aleatoire( param->nbChars, param->upper, param->lower, param->number, param->charac, param->genTime, param->secWait );

      return 0;
}



//********************************************************************
// Nom de la procédure: main
// Description        : Procédure principale
// Entrés             : argc, argv
// Sorties            : none
// Retour             : EXIT_SUCCESS
//********************************************************************
int main( int argc, char* argv[] )
{
    try{
    	gerer( parseArgs(argc, argv) );
    }
    catch( char fuck )
    {
    	GESTION_ERREUR( true );
    }

    return EXIT_SUCCESS;
}
