#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int length(char* string)
{
	return strlen(string)+1;
}

int length_manual(char* string)
{
	int i=0;
	while (string[i]!='\0')
	{
		i++;
	}
	return i+1;
}


int digits(char* string)
{
	int i=0;
	int j=0;

	while(string[i]!='\0')
	{
		if ( ((int)string[i] > 47) && ((int)string[i] < 58) )
			//faisable aussi avec if string[i] >='0' && <= '9'
		{
			j++;
		}
		i++;
	}
	return j;
}


int characters(char* string)
{
	int i=0;
	int j=0;

	while(string[i]!='\0')
	{
		if ( (((int)string[i] > 96) && ((int)string[i] < 123)) || (((int)string[i] > 64) && ((int)string[i] < 91)))
			//faisable aussi avec string[i]>='a' && <='z' || les majs...
		{
			j++;
		}
		i++;
	}
	return j;
}


char* reverse(char* string)
{
	char* buffer;	// on pourrait traiter directement sur string, car c'est une copie et pas le vrai !
	int i=0;

	buffer=calloc(length(string), sizeof(char));
	if(!buffer)
	{
		printf("In fuction reverse, 'buffer' calloc failed");
		exit(2);
	}

	while(string[i]!='\0')
	// Au lieu de parcourir toute la chaîne, on pourrait faire que la moitié.
	// Voir code corrige.c. On peut faire une boucle
	// while(j < k) avec j initialisé à 0 et k = length-1. A chaque tour de boucle, j++ et k--.
	{
		buffer[i]=string[length(string)-i-2];
		i++;
	}
	return buffer;
}

int find(char* string, char c)
{
	for(int i=0;i<length(string)-1;i++)
	{
		if (string[i]==c)
		{
			return i+1; //seul endroit où on compte en langage humain, pas en langage machine
		}
	}
	return -1;
}


//moyen de faire ça beaucoup mieux, voir corrige.c
char* charToBits(char c)
{
	char* buffer;
	buffer=calloc(8,sizeof(char));
	if(!buffer)
	{
		printf("In function charToBits, 'buffer' calloc failed");
		exit(2);
	}

	int i=0;

	while(c)
	{
		if (c & 1)
		{
			buffer[i]='1';
		}
		else
		{
			buffer[i]='0';
		}
		i++;
		c >>= 1;
	}
	buffer=reverse(buffer);

	return buffer;
}

//moyen de faire ça beaucoup mieux, voir corrige.c
char* bits(char* string, int j) //l'int est pour savoir si on printf ou pas.
	//seul moyen simple trouvé et fonctionnel pour supprimer l'output
	//pour les fonctions qui vont ré-utiliser bits()
{
	int i=0;

	char* buffer;
	buffer=calloc(8*(length(string)),sizeof(char));
	if(!buffer)
	{
		printf("In function bits, 'buffer' calloc failed");
		exit(2);
	}


	while(string[i]!='\0')
	{
		if(j==1)
		{
			printf("Caractère courant : %c ; Valeur décimale : %d ; Valeur binaire : %s\n", string[i], (int)string[i], charToBits(string[i]));
		}

		strcat(buffer,charToBits(string[i]));
		i++;
	}
	return buffer;
}


//moyen de faire ça beaucoup mieux, voir corrige.c
char* flip(char* string)
{
	int i=0;
	int j=0;

	//il faut désactiver l'affichage caractère par caractère des printf de la fonction bits()
	//technique du bled trouvée sur stackoverflow :
	//génère des warnings

	//	int old_stdout = dup(1);
	//	freopen("/dev/null","w",stdout);
	//	char* bitsOfString=bits(string);
	//	fclose(stdout);
	//	stdout= fdopen(old_stdout,"w");
	//bloque tout printf interne à la fonction suivante............

	char* bitsOfString=bits(string,0);

	char* temp = calloc(8,sizeof(char));
	char* outbuf = calloc(length(string),sizeof(char));

	if(!(bitsOfString&&temp&&outbuf))
	{
		printf("In function flip, 'bitsOfString' or 'temp' or 'outbuf'  calloc failed");
		exit(2);
	}

	while(string[i]!='\0')
	{

		memcpy(temp,&bitsOfString[i*7],7); //on extrait le substring de 7 caractères
		temp[7]='\0';

		for(j=0;j<7;j++)
		{
			temp[j]^=1; //on flip chacun des caractères
		}

		//on convertit ces 7 chiffres binaires inversés en un char qui est affecté à la valeur de sortie
		//pour ce faire, on a du faire string binaire -> int -> char.
		//On pourrait sauter des étapes, mais en ne reprenant le code de bits() pour cette fonction et celle d'en-dessous. 
		outbuf[i] = (char) strtol(temp,NULL,2);
		i++;
	}

	//printf("Une fois flip/NOT : %d\n", outbuf[2]);

	free(temp);
	free(bitsOfString);
	temp=NULL;
	bitsOfString=NULL;

	return outbuf;
}



char* permute_bit_fort_faible(char* string)
{
	//presque le même algorithme que pour la question précédente

	int i=0;
	int j=0;
	char swap;

	//il faut désactiver l'affichage caractère par caractère des printf de la fonction bits()
	//technique du bled trouvée sur stackoverflow :
	//génère des warnings

	//int old_stdout = dup(1);
	//freopen("/dev/null","w",stdout);

	char* bitsOfString=bits(string,0);

	//fclose(stdout);
	//stdout= fdopen(old_stdout,"w");


	char* temp = calloc(8,sizeof(char));
	char* outbuf = calloc(length(string),sizeof(char));

	if(!(bitsOfString&&temp&&outbuf))
	{
		printf("In function permute_bit_fort_faible, 'bitsOfString' or 'temp' or 'outbuf'  calloc failed");
		exit(2);
	}

	while(string[i]!='\0')
	{

		memcpy(temp,&bitsOfString[i*7],7); //on extrait le substring de 7 caractères
		temp[7]='\0';

		//on swap les bits de poids fort et de poids faible
		//c'est du binaire, donc pas besoin de swap, juste de flip..
		swap = temp[0];
		temp[0]=temp[6];
		temp[6]=swap;

		//on convertit ces 7 chiffres binaires inversés en un char qui est affecté à la valeur de sortie
		//pour ce faire, on a du faire string binaire -> int -> char
		//On pourrait sauter des étapes, mais en ne reprenant le code de bits() pour cette fonction et celle d'au-dessus. 

		outbuf[i] = (char) strtol(temp,NULL,2);
		i++;
	}

	//printf("Une fois permutée fort-faible : %d\n", outbuf[2]);

	free(temp);
	free(bitsOfString);
	temp=NULL;
	bitsOfString=NULL;

	return outbuf;
}


char* affichage_texte(char* input_binaire)
{//demandait depuis stdin, pas depuis un argument
	//presque le même algorithme que pour la question précédente

	int i=0;
	int j=0;

	char* temp = calloc(8,sizeof(char));
	char* outbuf = calloc(3,sizeof(char));

	if(!(temp&&outbuf))
	{
		printf("In function flip, 'temp' or 'outbuf'  calloc failed");
		exit(2);
	}

	while(input_binaire[i]!='\0')
	{
		memcpy(temp,&input_binaire[i*7],7); //on extrait le substring de 7 caractères

		if(find(temp,'\0')==-1) //test pour savoir si l'on est au dernier caractère
		{
			temp[7]='\0';
		}
		else
		{
			memcpy(temp,&temp[0],find(temp,'\0')); //on extrait le substring du dernier char
			outbuf[i] = (char) strtol(temp,NULL,2);
			goto finish; // et on sort
		}

		//on convertit ces 7 chiffres binaires en un char qui est affecté à la valeur de sortie
		//pour ce faire, on a du faire string binaire -> int -> char
		//On pourrait sauter des étapes, mais en ne reprenant le code de bits() pour cette fonction et celle d'au-dessus. 

		outbuf[i] = (char) strtol(temp,NULL,2);
		i++;
	}

finish:
	free(temp);
	temp=NULL;

	return outbuf;
}



int main(int argc, char** argv)
{
	//EXO 1
	printf("Length : %d\n",length("foobar"));	
	printf("Manual length : %d\n",length_manual("foobar2"));
	printf("Digits : %d\n",digits("foo123az82"));
	printf("Characters : %d\n",characters("foobar34 AZE"));
	//la fonction symbols c'est pareil avec des plages différentes
	printf("Reverse : %s\n",reverse("foobar"));
	printf("Find : %d\n",find("blablablaou",'u'));
	printf("Find qui doit échouer : %d\n",find("blablablaou",'z'));


	//EXO 2
	char* string="foobar";
	printf("\nChaîne de caractère choisie pour les fonctions de l'exercice 2 : %s\n\n",string);

	printf("Equivalent en bits : %s\n\n",bits(string,1));
	printf("Chaîne de caractères flip/NOT : %s\n",flip(string));
	printf("Chaîne de caractères permutée fort-faible : %s\n\n",permute_bit_fort_faible(string));

	printf("Ces caractères sont non-imprimables. Pour vérifier que ça a bien fonctionné, il suffit de décommenter la dernière ligne avant le return pour vérifier caractère par caractère.\n\n");

	//char* string2 = "110011011011111101111100001";

	char line[256];
	int i;
	printf("Veuillez rentrer la châine binaire (maximum 256 caractères, pas obligatoirement multiple de 7) : \n ");
	if(fgets(line,sizeof(line),stdin)) { // prends en compte le \0
		if(1 == sscanf(line, "%s")){ // on pourrait forcer avec %7s mais bon
			printf("Affichage du texte corresponsant à l'input binaire : %s\n\n", affichage_texte(line));
		}
	}
	
	return 1;
}
