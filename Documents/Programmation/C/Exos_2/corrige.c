#include <stdio.h> //Inclure la bibliothèque standard du C
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// EXERCICE 1 : Le passage par valeur / adresse (Sur des entiers)
/*
   Réaliser une fonction qui reçoit un entier par adresse. Modifier cet entier dans la fonction. Imprimer
   cet entier avant l’appel de fonction, pendant l’appel de fonction (après la modif), puis après l’appel de
   fonction. Conclure.
   */
void F_adr(int * A)
{
	int New_val = 38;
	printf("Pendant : A = %d\n", *A);
	//A = &New_val; 
	*A = New_val;
	printf("pendant ( apres modif ): A = %d\n", *A);
}



// EXERCICE 2 : Le passage par valeur / adresse (Sur des éléments d’un tableau)
/*
   1. et 2. Réaliser une fonction affiche_n qui prend deux paramètres, un tableau d’entiers et le nombre de cases n à
   afficher et qui affiche n valeurs du tableau.
   */
void affiche_n(int tab[], int n)
{
	int i;
	for (i=0; i<n; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
}

/*
   3. Passer, par valeur, le 5-ème élément du tableau à une fonction passe_valeur qui affiche cette valeur.
   */
void passe_valeur(int elt)
{
	printf("%d\n", elt);
}
/*
   4. Passer, par adresse, l’adresse du 5-ème élément du tableau à une fonction passe_adresse et utiliser la fonc-
   tion affiche_n pour afficher trois éléments.
   */

void passe_adresse(int * ELT)
{
	int *NEW_TAB;
	NEW_TAB = ELT;

	affiche_n(NEW_TAB, 3);
	printf("\n");
}


// EXERCICE 3 : Allocation dynamique de mémoire

/*
   1. Écrire une fonction alloc_tab qui alloue puis renvoie un tableau alloué de mémoire.
   */

int * alloc_tab (int N)
{
	int* tab = malloc(N*sizeof(int));
	return tab;
}



// EXERCICE 4 : Un pointeur de pointeur
/*
   1. Écrire une fonction alloc_mat qui alloue de la mémoire à une matrice (tableau de pointeurs de pointeurs)
   d’entiers. Cette fonction prend en paramètres les dimensions de la matrice à savoir le nombre de lignes
   (nb_l) et de colonnes (nb_c) et renvoie la matrice en sortie.
   */
int** alloc_mat(int nb_l, int nb_c)//allocation de mémoire à la matrice
{
	int i;
	int ** mat = malloc(nb_l*sizeof(int*));
	for (i=0; i<nb_l; i++)
	{
		mat[i] = malloc(nb_c*sizeof(int));
	}
	return mat;
}


/*
   2. Écrire une fonction lib_mat dont le but est de désallouer de la mémoire à une matrice.
   */
void lib_mat(int ** mat, int nb_l)//pour libérer totalement la matrice 
{
	int i;
	for ( i=0 ; i<nb_l ; i++)
	{
		free(mat[i]);
		mat[i] = NULL ;
	}
	free(mat);
	mat = NULL;
}


/*
   3. Écrire une fonction remp_mat qui prend en paramètres une matrice ainsi 
   que ses dimensions et qui remplit chaque ligne avec des entiers aléatoires 
   compris entre 1 et 9.
   */
void remp_mat(int ** mat, int nb_l, int nb_c) //remplire les cases mémoires d'une matrice
{
	int i, j; 
	for (i=0; i<nb_l; i++)
	{
		for (j=0; j<nb_c; j++)
		{
			mat[i][j]=rand()%19 +1;
		}
	}
}

/*
   4. Écrire une fonction affiche_mat qui permet d'afficher une matrice nb_l * nb_c dont le nom est donné en paramètre.
   */
void affiche_mat(int ** mat, int nb_l, int nb_c) //afficher une matrice
{
	int i, j;
	for (i=0; i<nb_l; i++)
	{
		for (j=0; j<nb_c; j++)
		{
			//printf("%d ", mat[i][j]);
			printf("%d ", *(*(mat+i)+j));
		}
		printf("\n");
	}
}


/*
   5. Écrire une fonction test_mat qui appelle toutes ces fonctions et qui permet de déclarer, remplir puis
   afficher une matrice quelconque (exp 10 × 30). Ne pas oublier de désallouer la matrice.
   */

void test_mat()
{
	int nb_l, nb_c;
	printf("Saisir nb_l et nb_c :\n");
	scanf("%d %d", &nb_l, &nb_c);
	int ** mat = alloc_mat(nb_l, nb_c);
	remp_mat(mat, nb_l, nb_c);
	affiche_mat(mat, nb_l, nb_c);
	lib_mat(mat, nb_l);
}



// EXERCICE 5 : les fichiers
/*
   1. Ecrire une fonction affiche_mat_ds_fic qui affiche une matrice dans un fichier
   */

void affiche_mat_ds_fic(int ** mat, int nb_l, int nb_c, FILE * FIC)
{
	int i, j;
	for (i=0; i<nb_l; i++)
	{
		for (j=0; j<nb_c; j++)
		{
			fprintf(FIC, "%d ", mat[i][j]);
		}
		fprintf(FIC, "\n");
	}
}


/*
   2. Ecrire une fonction remp_mat_via_fic qui charge une matrice depuis un fichier
   */
void remp_mat_via_fic(int ** mat, int nb_l, int nb_c, FILE * FIC) //remplire les cases mémoires d'une matrice
{
	int i, j, val;

	for (i=0; i<nb_l; i++)
	{
		for (j=0; j<nb_c; j++)
		{
			fscanf(FIC, "%d", &val);
			mat[i][j]=val;
		}
	}
}


// EXERCICE 6 : les fichiers
/*
   1. Fonction qui calcule puis retourne le nombre de lignes d'un fichier donné 
   en paramètre
   */
int Nb_lignes_fic(FILE * fic)
{
	int nb_l, el;
	nb_l=0;

	if (fic == NULL)
	{
		printf("FILE ERROR\n");
		return -1;
	}

	do
	{
		el = fgetc(fic);
		if (el == '\n') /*ou el==10*/
		{
			nb_l++;
		}
	}while (el != EOF);

	return nb_l;
}


int Recherche_motif (FILE * FIC, char * motif)
{
	int i, l, num_l, num_l_p, found;
	char c;
	i=0;
	l=strlen(motif);
	num_l=1;
	num_l_p = 1;
	found = 0;
	while ((c=fgetc(FIC)) != EOF) /*Récupération des élémtents char par char*/
	{
		if (c == '\n') /*si on change de ligne, on met à jour le numéro de ligne courante*/
		{
			num_l++;
		}

		if (c == motif[i]) /*Si le char récupéré correspond à un char du motif*/
		{
			if (i==(l-1)) /*Si un motif est épuisé*/
			{ 
				i=0; /*on réinitialise son indice de parcours*/
				found++; /*on incrémente le nombre total de motifs trouvés*/
				if (num_l == num_l_p)/*Si le motif trouvé est situé sur la même ligne que le précédent*/
				{
					printf("%d ", num_l); /*on affiche sur la même ligne*/
				}
				else
				{
					printf("\n%d ", num_l); /*on revient à la ligne car le motif trouvé est sur une nouvelle ligne*/
					num_l_p = num_l; /*on met à jour la variable num_l_p qui prend le numéro de la ligne courante*/
				}
			}
			else
			{
				i++;
			}
		}
		else
		{
			i=0;
		}

	}
	if (found == 0)
	{
		printf("LE TEXTE NE CONTIENT PAS LE MOTIF \"%s\" !!!", motif);
	}
	else
	{
		printf("\n%d MOTIF%c TROUVE%c !!!", found, (found>1)?'S':' ', (found>1)?'S':' ');
	}
	printf("\n");
	return found;

}





//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{
	srand(time(NULL));
	printf("------------EX1--------------\n");
	int A;
	A=18;
	printf("Avant appel : A = %d\n", A); 
	F_adr(&A);
	printf("Apres appel : A = %d\n", A);
	printf("----------FIN EX1------------\n");

	printf("------------EX2--------------\n");
	int i, N, n;
	N=10; n=8;
	int tab[N];
	for (i=0; i<N; i++) //Remplissage du tableau
	{
		tab[i]=i;
	}
	affiche_n(tab, n);
	passe_valeur(tab[4]);
	passe_adresse(&tab[4]);
	printf("----------FIN EX2------------\n");

	printf("------------EX3--------------\n");
	int C;
	printf("ENTREZ LA TAILLE DE VOTRE TABLEAU : ");
	scanf("%d",&N);
	int * mon_tab = alloc_tab (N);
	for (i=0; i<N; i++)
	{
		mon_tab[i] = rand()%80 + 15;
	}
	printf("QUELLE CASE SOUHAITEZ-VOUS AFFICHER ? ");
	scanf("%d",&C);
	printf("%d\n", *(mon_tab+C)); //affichage de tab[C] après avoir determiné son adresse mémoire
	free(mon_tab);
	printf("----------FIN EX3------------\n");

	printf("------------EX4--------------\n");
	test_mat();
	printf("----------FIN EX4------------\n");


	printf("------------EX5--------------\n");
	int nb_l, nb_c;
	nb_l=20; nb_c=20;
	int ** mat = alloc_mat(nb_l, nb_c);
	//remp_mat(mat, nb_l, nb_c);

	/*FILE * FIC = fopen("matrice.txt", "w");
	  affiche_mat_ds_fic(mat, nb_l, nb_c, FIC);
	  lib_mat(mat, nb_l);
	  fclose(FIC);*/
	/*FILE * FIC = fopen("matrice.txt", "r");
	  remp_mat_via_fic(mat, nb_l, nb_c, FIC);
	  affiche_mat(mat, nb_l, nb_c);
	  fclose(FIC);
	  printf("----------FIN EX5------------\n");
	  */
	printf("------------EX6--------------\n");
	char * motif = malloc(20*sizeof(char));
	FILE * FICT = fopen("blague.txt", "r");
	nb_l = Nb_lignes_fic(FICT);
	printf("NB_LIGNES DU TEXTE = %d\n", nb_l);
	fseek(FICT, 0, SEEK_SET );
	printf("Saisir un motif à chercher : \n");
	scanf("%19s", motif);
	Recherche_motif (FICT, motif);
	fclose(FICT);
	printf("----------FIN EX6------------\n");

	return 0;
}
