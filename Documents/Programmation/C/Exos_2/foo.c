#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//EXO 1
void modifyInt(int* a)
{
	printf("Entier pendant la fonction : %d\n", *a);
	(*a)++;//modifiera une copie sauf si je vais vraiment chercher la valeur à son adresse
}

//EXO 2
void affiche_n(int* tab, int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		printf("%dème valeur du tableau : %d\n",i,tab[i]);
	}
}

void passe_valeur (int a) { printf("Voici l'entier : %d\n",a); }
void passe_adresse (int* a) 
{
	printf("Voici l'entier et les trois suivants :\n");
	affiche_n(a,3);
}

//EXO 3
int size = 0; // pour que plus tard on affiche pas plus de caractères qu'alloués

int* alloc_tab()
{
	int* outbuf = NULL;
	int i=0;
	int line;

	printf("\nVeuillez entrer le nombre de blocs à allouer.\n");
	if(1 == scanf("%d",&line)){
		if(line!=0)
		{
			outbuf = malloc( line * sizeof(int) );
			if(!outbuf)
			{
				printf("In function alloc_tab, 'outbuf' malloc failed\n");
				exit(2);
			}
			for(i=0 ; i < line ; i++)
			{
				outbuf[i] = (rand()%80)+15;
			}
			size = line;
		}
	}
	return outbuf;
}

//EXO 4

int** alloc_mat(int nb_l, int nb_c)
{
	int i=0;
	int** outbuffer = (int**) malloc(nb_l * sizeof(int*));
	if(!outbuffer)
	{
		printf("In function alloc_tab, 'outbuffer' malloc failed\n");
		exit(2);
	}

	for(i = 0; i < nb_l ; i++) // car même nombre de colonnes pour chaque ligne
	{
		outbuffer[i] = malloc (nb_c * sizeof(int));
		if(!outbuffer[i])
		{
			printf("In function alloc_tab, 'outbuffer[%d]' malloc failed\n",i);
			exit(3);
		}
	}
	return outbuffer;
}

void lib_mat(int** mat, int nb_l)
{
	int i=0;
	for(i = 0; i < nb_l ; i++) //obligé de lui filer nb_l
	{
		free(mat[i]);
		mat[i] = NULL;
	}
	free(mat);
	mat = NULL;
}

void remp_mat(int** mat, int nb_l, int nb_c)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < nb_l ; i++)
	{
		for(j = 0; j < nb_c ; j++)
		{
			mat[i][j] = (rand()%10); // avec [][] on va directement à la bonne adresse du coup... on ne touche pas une copie
		}
	}
}

void affiche_mat(int **mat, int nb_l, int nb_c)
{
	int i = 0;

	for(i = 0 ; i < nb_l ; i++)
	{
		printf("\n%dème ligne : \n", i);
		affiche_n( (*(mat + i)) , nb_c);//Attention ! c'est bien *(mat+i) sinon on décale dans les lignes
			// on pourrait faire *(*(mat+i)+j)
	}
}

void test_mat(int nb_l, int nb_c)
{
	int ** mat = alloc_mat(nb_l,nb_c);
	remp_mat(mat,nb_l,nb_c);
	affiche_mat(mat,nb_l,nb_c);
	lib_mat(mat,nb_l);
}


//EXO 5
void affiche_mat_ds_fic(int **mat, int nb_l, int nb_c)
{
	//même chose que pour affiche_mat mais dans un fichier
	
}




int main(int argc, char** argv)
{
	srand(time(NULL));

	//EXO 1
	int* a;
	a = calloc (1, sizeof(int));
	(*a) = 2;

	printf("Entier avant la fonction : %d\n", *a);
	modifyInt(a);
	printf("Entier après la fonction : %d\n", *a);
	free(a);
	a = NULL;

	//EXO 2
	int b [10]  = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10};
	affiche_n(b,3);
	int c = 2;
	passe_valeur(c);
	passe_adresse(b+5); // b = adresse. donc on offset de 5

	//EXO 3
	int* d = alloc_tab();
	affiche_n(d,size);

	printf("Veuillez écrire quelle case vous souhaitez afficher (en machine, on commence à 0):\n");

	c = 0;
	if(1 == scanf("%d", &c)){
		printf("Case numéro %d : %d\n",c,*(d+c));
	}
	free(d);
	d = NULL;

	//EXO 4
	test_mat(3,5);

	//EXO 5
	

	return 1;
}
