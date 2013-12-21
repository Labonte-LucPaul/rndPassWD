/*
  Name: rndPassWD.cpp
  Copyright: LPL.Corporation©2006
  Author: Luc Paul Labonté
  Date: 21-01-06 14:38
  Description: générer des mot de passes aléatoirement

  Modifi� le 24-06-2010.
  Ajout de la définition WIN32 pour windows, avoir le temps
  (Sleep) fonctionne pour windows. Also a print version system
  and copyright updated.
*/

// nbChar, l, u, n, a
// printf ("%c"); output of a value of a ascii char

#define _WIN32_	// Activate only if on windows

#define VER "2.3"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;



//********************************************************************
// Nom de la proc�dure: GESTION_ERREUR
// Description        : Gère les erreures d'entrée de paramètre
// Entrés             : zeFuck
// Sorties            : none
// Retour             : 0
//********************************************************************
int GESTION_ERREUR( char ZeFuck )
{
      cout << ZeFuck << "\n\n\t";

      cout << "\n\n\t\t\7 *** ERREUR DE PARAMETRES!!! ***\n\n"
           << "\n\tLa syntaxe correct est: \n"
           << "\n\trndPassWD [nbChar] [l | u | n | a | -] [generated time] [sec to wait]\n"
           << "\n\n   nbChar: Nombres de caract�res du mot de passe.(0-999)\n"
           << "   l     : Pour LowerCase.\n"
           << "   u     : Pour UpperCase.\n"
           << "   n     : Pour Nombres.\n"
           << "   a     : Pour autres Caract�res ASCII\n\n"
	   << "   generated time : Number of password to generate\n"
	   << "   sec to wait    : Number of sec of intervale between the password generated\n\n"
           << "NOTE: Entrez le caractere \'-\' pour indiquer "
           << "que l'option ne sera pas activee." ;

      cout << endl << endl << "Version: " << VER << endl;
      cout << "\nLPL.Corporation�2006 - 2010\n\n";

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
    int i;
    int j;

    char passWD[nbCaracteres];


    if( secSleep <= 1 )
    {
		cout << "\nMust be higher or equal then 1.\n";
		cout << "We will use 1 for now!\n";
		secSleep = 1;
    }

    cout << "\n\nNouveau mot de passe: \n";

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

     	 	} // fin while
	     	// cout << "Nouveau mot de passe: \n ";
     	     	for(i=0;i<nbCaracteres;i++)
     	     	{
	        	cout << passWD[i];
             	}
	     	cout << "\n";
	     /*   cout << "  ]\n\nC'est le temps d'activer "
		  	 << "mon keylogger...lol ;)\n";
		  cout << "\n\nMerci d'avoir utiliser rndPassWD :)\n"
		       << "Programmer par: Luc Paul Labonté\n"
		       << "CopyRight 2006  LPL.Corporation(c)2006\n\n\7";*/
    		} // fin du try

    	catch( char fuck )
    	{
     		GESTION_ERREUR( fuck );
    	}

    }// fin j for

    	cout << "\n\nMerci d'avoir utiliser rndPassWD2 :)\n"
	     << "Programmer par: Luc paul Labonte\n"
	     << "CopyRight 2006-2010 LPL.Corporation(c)2006-2010\n\n";
    return 0;
}// fin de la procedure


//********************************************************************
// Nom de la procédure: GERER
// Description        : Gérer les paramètres
// Entrés             : nombreChar, Minuscules, Majuscules,
//                                              Chiffres, carASCII
// Sorties            : none
// Retour             : 0
//********************************************************************
int GERER( char *nombreChar[3], char *Minuscules[], char *Majuscules[],
           char *Chiffres[], char *carAscii[], char *loop[], char *Wait[] )
{
     // Variables
     bool setMinuscule  = false;
     bool setMajuscule  = false;
     bool setChiffres   = false;
     bool setCarAscii   = false;
     int  nbChar        = atoi( nombreChar[0] );
     int  nbLoop	= atoi( loop[0] );
     int  secWait	= atoi( Wait[0] );

     cout << "Parametres entres: ";
     cout << *nombreChar << *Minuscules[0] << *Majuscules[0]
          << *Chiffres[0] << *carAscii[0] << "\n\n" ;

     if( *Minuscules[0] != '-' )
     	   setMinuscule = true;
     if( *Majuscules[0] != '-' )
     	   setMajuscule = true;
     if( *Chiffres[0] != '-' )
     	   setChiffres = true;
     if( *carAscii[0] != '-' )
     	   setCarAscii = true;

     aleatoire( nbChar, setMajuscule, setMinuscule, setChiffres, setCarAscii, nbLoop, secWait );

      return 0;
}



//********************************************************************
// Nom de la proc�dure: main
// Description        : Procédure principale
// Entrés             : argc, argv
// Sorties            : none
// Retour             : EXIT_SUCCESS
//********************************************************************
int main( int argc, char *argv[] )
{
    char fuck = '\0';

    try{

	    if( argc <= 7 )
	    {
	  	 GESTION_ERREUR( fuck );
	  	 cout << endl << endl << "Exit 1: main:GESTION_ERREUR:argv <= 7, too few arguments!" << endl;
	  	 system( "PAUSE" );
	     exit( 1 );
	    }
	    else
	    {
	        GERER( &argv[1], &argv[2], &argv[3], &argv[4], &argv[5], &argv[6], &argv[7] );
	    }
    }
    catch( char fuck )
    {
    	     GESTION_ERREUR( fuck );
    }

    system("PAUSE");

    return EXIT_SUCCESS;
}
