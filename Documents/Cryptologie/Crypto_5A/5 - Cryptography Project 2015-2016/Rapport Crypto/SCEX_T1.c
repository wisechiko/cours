#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define POLY1 0x10000000016L // = 0x2DL
#define POLY2 0x40000001995L // = 0x332BL
#define POLY3 0x400000000034L // = 0x69L

unsigned char motpar64( uint64_t word )
{
	word ^=(word>>32);
	word ^=(word>>16);
	word ^=(word>> 8);
	word ^=(word>> 4);
	word ^=(word>> 2);
	word ^=(word>> 1);
  
	return (unsigned char)(word & 1LL);
}

int cipher_T1( unsigned char * clear, uint32_t length, unsigned char * ciphered, uint64_t r1, uint64_t r2, uint64_t r3 )
{
	unsigned int i;
	unsigned int count = 0U;
	unsigned char j;
	unsigned char x;
	unsigned char reg;
	unsigned char block;
	unsigned char f1[8] = {0,0,0,1,0,1,1,1};
	unsigned char f2[8] = {0,1,0,0,1,0,1,1};
	unsigned char f3[8] = {0,1,0,1,0,0,1,1};

	if( clear == NULL || ciphered == NULL || length <= 0 )
		return -1;

	for( i = 0 ; i < length ; i++ )
	{
		block = 0;
		for( j = 0 ; j < 8 ; j++ )
		{
			if(j%3 == 0)
				x = f1[(r1 & 1) | ((r2 & 1) << 1) | ((r3 & 1) << 2)];
			else if (j%3 == 1)
				x = f2[(r1 & 1) | ((r2 & 1) << 1) | ((r3 & 1) << 2)];
			else
				x = f3[(r1 & 1) | ((r2 & 1) << 1) | ((r3 & 1) << 2)];

			block |= (x << j);
      
			reg = motpar64(r1 & POLY1);
			r1 >>=1;
			r1 |= ((uint64_t)reg << 40);
      
			reg = motpar64(r2 & POLY2);
			r2 >>=1;
			r2 |= ((uint64_t)reg << 42);

			reg = motpar64(r3 & POLY3);
			r3 >>=1;
			r3 |= ((uint64_t)reg << 46);

			count++;
		}
		ciphered[ i ] = clear[ i ] ^ block;
	}

	return 0;
}

void help( void )
{
	printf("Usage : <input> <output> <key>\n");
}

int main( int argc, char * argv[] )
{
	FILE * input = NULL, * output = NULL;
	uint64_t r1, r2, r3;
	uint32_t length = 0;
	int i = 0;
	unsigned char * clear = NULL, * ciphered = NULL;

	//Usage checks
	if( argc != 4 )
	{
		help();
		goto end;
	}
	
	//Input file opening
	input = fopen( argv[1], "rb" );
	if( input == NULL )
	{
		printf("Error opening input file\n");
		help();
		goto end;
	}
	
	//Output file opening
	output = fopen( argv[2], "wb" );
	if( output == NULL )
	{
		printf("Error opening output file\n");
		help();
		goto end;
	}

	//Setting registers with the key
	//r1
	r1 = argv[3][0] + (argv[3][1] << 8) + (argv[3][2] << 16) + (argv[3][3] << 24) +
		((uint64_t) argv[3][4] << 32) + ((uint64_t) (argv[3][5] & 0x01) << 40);

	//r2
	r2 = (argv[3][5] >> 1) + (argv[3][6] << 7) + (argv[3][7] << 15) + (argv[3][8] << 23) +
		(argv[3][9] << 31) + (((uint64_t) argv[3][10] & 0x0F) << 39);

	//r3
	r3 = (argv[3][10] & 0xF0 >> 4) + (argv[3][11] << 4) + (argv[3][12] << 12) + (argv[3][13]
		<< 20) + ((uint64_t) argv[3][14] << 28) + ((uint64_t) argv[3][15] << 36) +
		(((uint64_t) argv[3][16] & 0x03) << 44);

	//Getting input file length
	fseek( input, 0, SEEK_END );
	length = (uint32_t)ftell( input );
	fseek( input, 0, SEEK_SET );

	//Allocation
	clear = (unsigned char*)malloc( length * sizeof(char) );
	if( clear == NULL )
	{
		printf("Error allocating input clear text\n");
		goto end;
	}
	ciphered = (unsigned char*)malloc( length * sizeof(char) );
	if( ciphered == NULL )
	{
		printf("Error allocating output ciphered text\n");
		goto end;
	}

	//Read the input clear file
	if( fread( clear, length, 1, input ) != 1 )
	{
		printf("Error reading input clear file\n");
		goto end;
	}
	

	// Cipher / Decipher
	cipher_T1( clear, length, ciphered, r1, r2, r3 );

	// Outputting result	
	for(i=0;i<length;i++)
		fprintf(output,"%02X",ciphered[i]);

	end:
	
	if( input != NULL )
	{
		fclose( input );
		input = NULL;
	}

	if( output != NULL )
	{
		fclose( output );
		output = NULL;
	}

	if( clear != NULL )
	{
		free( clear );
		clear = NULL;
	}

	if( ciphered != NULL )
	{
		free( ciphered );
		ciphered = NULL;
	}

	return 0;
}