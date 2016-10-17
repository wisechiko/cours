#include <stdio.h> //Inclure la bibliothèque standard du C
#include <stdlib.h>
#include <math.h>
#include <string.h>


//EXERCICE Fonctions de base sur les chaînes de caractères
//1. Écrire une fonction LENGTH qui retourne la longueur d’une chaîne de caractères.

int LENGTH (char * STR)
	//fonction LENGTH qui retourne la longueur d’une chaîne de caractères
{
	int l;
	l = strlen(STR);
	return l;
}

/*2. Écrire une fonction DIGITS qui prend en paramètre une chaîne de caractères et retourne le nombre de
  chiffres qu'elle contient, et une fonction CHARACTERS qui retourne le nombre de lettres. Afficher finale-
  ment dans la fonction main : le nombre de chiffres, le nombre de lettres, ou même le nombre d'autres symboles
  */

int DIGITS (char * STR)
	/*fonction DIGITS qui prend en paramètre une chaîne de caractères et retourne le nombre de chiffres
	  qu'elle contient*/
{
	int i, l, nb;
	char c; 
	nb=0;
	l = LENGTH(STR);
	for (i=0; i<l; i++)	
	{
		c = STR[i];
		if (c>='0' && c<='9')
		{
			nb++;
		}
	}
	return nb;
}


int CHARACTERS (char * STR)
	/*fonction CHARACTERS qui prend en paramètre une chaîne de caractères et retourne le nombre de lettres qu'elle contient
	*/
{
	int i, l, nb;
	char c; 
	nb=0;
	l = LENGTH(STR);
	for (i=0; i<l; i++)
	{
		c = STR[i];
		if (c>='a' && c<='z')
		{
			nb++;
		}
	}
	return nb;
}


/*
   3. Écrire une fonction REVERSE qui prend en paramètre une chaîne de caractères, et retourne la chaîne de
   caractères dont l'ordre des caractères a été inversé.
   */

char* REVERSE (char * STR)
{
	int j, k, l;
	char c1; 
	l=LENGTH(STR);
	j=0; k=l-1;

	while(j < k)
	{
		c1 = STR[j];
		STR[j] = STR[k];
		STR[k] = c1;
		j=j+1;
		k=k-1;
	}
	return STR; // Ca ne modifie pas l'originale ! c'est une copie.
}



/*4. Écrire une fonction FIND qui prend en paramètre une chaîne de caractères et un caractère, et retourne
  l’indice de la première occurrence du caractère dans la chaîne de caractères (retourne -1 si le caractère
  n’existe pas).
  */

int FIND (char * STR, char C)
{
	int i, l, ind;
	l = LENGTH(STR);
	ind=-1;
	for (i=0; i<l; i++)
	{
		if (STR[i]==C)
		{
			ind=i;
			break;
		}
	}
	return ind;
}


/*EXERCICE manipulation bit à bit*/

/*
   1. Écrire une fonction BITS qui prend en paramètre une chaîne de caractères et qui 
   affiche chaque caractère suivi de sa représentation en entier puis de sa représentation 
   en binaire (sur 7 bits). 
   */

void BITS (char * STR)
{
	int i, j, l;
	short unsigned bit;
	l=LENGTH(STR);
	for (i=0; i<l; i++)
	{
		printf("%c => %d => ", STR[i], STR[i]);
		for (j=6; j>=0; j--)
		{
			bit = (STR[i]>>j) & 1; /*recupération du bit via un masque de 1*/
			printf("%hu", bit); // %hu = unsigned short
		}
		printf("\n");
	}
}

/*
   2. Écrire une fonction FLIP qui prend en paramètre une chaîne de caractères et qui change 
   les bits (1->0, 0->1) de chaque caractère (7 bits) de la chaîne. Puis afficher la nouvelle chaîne.
   */
char * FLIP (char * STR)
{
	int i, j, l;

	l=LENGTH(STR);
	for (i=0; i<l; i++)
	{
		for (j=6; j>=0; j--)
		{
			STR[i] = STR[i]^(1<<j); /*XOR avec 1 pour flipper le bit*/
		}
	}
	return STR;
}
/*
   3. Écrire une fonction PERMUTE_BIT_FORT_FAIBLE prenant en paramètre une chaîne de 
   caractères et qui permute le bit de poids faible avec celui de poids fort pour chaque 
   caractère de la chaîne.
   */

char * PERMUTE_BIT_FORT_FAIBLE (char * STR)
{
	int l;
	short unsigned int i, fort, faible;
	l = LENGTH(STR);
	for (i=0; i<l; i++)
	{
		fort = (STR[i]>>6) & 1;
		faible = STR[i] & 1;
		if (fort != faible)
		{
			STR[i] = STR[i]^(1<<6); //on les flip
			STR[i] = STR[i]^1; //on les flip
		}
	}

	return STR;
}

/*
   4. Ecrire une fonction AFFICHAGE_TEXTE qui affiche le texte correspondant à une chaîne binaire saisie en 
   entrée standard.
   */  
char * AFFICHAGE_TEXTE ()
{
	int i, val;
	char * TEXTE = malloc(100*sizeof(char));
	char BITS[8];
	i=0;

	while (scanf("%7s", BITS) != EOF)
	{

		val = (BITS[0]=='1'?1:0)*64 + (BITS[1]=='1'?1:0)*32 + (BITS[2]=='1'?1:0)*16 + (BITS[3]=='1'?1:0)*8 + 
			(BITS[4]=='1'?1:0)*4 + (BITS[5]=='1'?1:0)*2 + (BITS[6]=='1'?1:0)*1;
		TEXTE[i] = val;
		i++;

	}

	return TEXTE;
}


int main (int argc, char * argv[])
{
	int L, CHI, CHA, F;
	//char * CHAINE = malloc(20*sizeof(char));
	char CHAINE[20];
	//char * CHAINE = malloc(20*sizeof(char));
	//char CHAINE[10];
	//char *CHA2;
	//strcpy(CHAINE,"bonjour94");
	//char * CHA2 = malloc(20*sizeof(char));
	scanf("%19s", CHAINE);
	L = LENGTH(CHAINE);
	printf("L= %d\n", L);
	CHI = DIGITS(CHAINE);
	printf("NB chiffres = %d\n", CHI);
	CHA = CHARACTERS(CHAINE);
	printf("NB caract = %d\n", CHA);
	//CHA2 = REVERSE(CHAINE);
	//printf("%s\n", CHA2);
	F = FIND(CHAINE, '9');
	//printf("%s\n", CHA2);
	printf("%d\n", F);

	/*PARTIE 2*/
	BITS (CHAINE);
	//CHA2 = FLIP (CHAINE);
	//CHA2 = PERMUTE_BIT_FORT_FAIBLE (CHAINE);
	printf("\n\n\n");
	//BITS (CHA2);
	//PERMUTE_BIT_FORT_FAIBLE (CHAINE);
	printf("%s\n", AFFICHAGE_TEXTE ());
	return 0;
}





































