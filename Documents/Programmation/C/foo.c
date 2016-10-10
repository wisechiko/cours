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
		{
			j++;
		}
		i++;
	}
	return j;
}


char* reverse(char* string)
{
	char* buffer;
	int i=0;

	buffer=calloc(length(string), sizeof(char));
	if(!buffer)
	{
		printf("In fuction reverse, 'buffer' calloc failed");
		exit(2);
	}

	while(string[i]!='\0')
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


char* bits(char* string)
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
		printf("Caractère courant : %c ; Valeur décimale : %d ; Valeur binaire : %s\n", string[i], (int)string[i], charToBits(string[i]));
		strcat(buffer,charToBits(string[i]));
		i++;
	}
	printf("Total en caractères : %s\n", string);
	printf("Total en binaire : %s\n",buffer);
	return buffer;
}


void flip(char* string)
{
	int i=0;
	char* bitsOfString=bits(string);
	char* outbuf = calloc(length(string),sizeof(char));

	while(string[i]!='\0')
	{
		for(int j=0;j<8;j++)
		{
			outbuf[i]=bitsOfString[i*8+j];
			outbuf[i] <<= 1;
		}
		i++;
	}
	printf("Une fois flip : %s\n", outbuf);
}

int main(int argc, char** argv)
{
	printf("Length : %d\n",length("foobar"));	
	printf("Manual length : %d\n",length_manual("foobar2"));
	printf("Digits : %d\n",digits("foo123az82"));
	printf("Characters : %d\n",characters("foobar34 AZE"));
	//la fonction symbols c'est pareil avec des plages différentes
	printf("Reverse : %s\n",reverse("foobar"));
	printf("Find : %d\n",find("blablablaou",'u'));
	
	char* string="foobar";
	bits(string);

	flip(string);
	//printf("bordel : %s\n",string);

	//char* foo="0110";
	//printf("bordel : %\n",a 
	return 1;
}
