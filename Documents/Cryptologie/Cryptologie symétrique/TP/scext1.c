#undef DEBUG
#include "include.h"

#define POLY1 0x332BLL 
#define POLY2 0x2DLL
#define POLY3 0x69LL

#define MASK1 0x7FFFFFFFFFFLL
#define MASK2 0x1FFFFFFFFFFLL
#define MASK3 0x7FFFFFFFFFFFLL

#define L1 42
#define L2 40
#define L3 46

mot64 motpar(mot64 w)
 {
  w ^= (w >> 32);
  w ^= (w >> 16);
  w ^= (w >>  8);
  w ^= (w >>  4);
  w ^= (w >>  2);
  w ^= (w >>  1);
  
  return(w & 1L);
 }

/**************************************************************/
/* Systeme de chiffrement par flot scex_t1. Ce systeme est un */
/* exemple de systeme avec trappe (version 1)                 */
/* La sortie est la somme des 3 fonctions                     */
/* La clef fait 131 bits (17 octets)                          */
/*                                                            */
/* Usage scex d|e infile outfile "clef"                       */
/*                                                            */
/* CBA FILIOL Eric                                            */
/**************************************************************/
int main(int argc, char * argv[])
 {
  register mot64 reg1, reg2, reg3, reb; 
  mot64 i, j;
  FILE * fin, * fout;
  mot08 outblock, lettre, f1[8] = {0,0,0,1,0,1,1,1}, f2[8] = {0,1,0,0,1,0,1,1}, f3[8] = {0,0,1,1,0,1,0,1}, x1, x2, x3;
  
  /***************************************/
  /*     Ouverture des fichiers          */
  /***************************************/
  fin = fopen(argv[2],"r");
  fout = fopen(argv[3],"w");

  /***************************************/
  /* Mise a la clef des registres        */
  /***************************************/
  reg1 = (mot64)(argv[4][0]) | ((mot64)(argv[4][1]) << 8) | ((mot64)(argv[4][2]) << 16) | ((mot64)(argv[4][3]) << 24) | ((mot64)(argv[4][4]) << 32) | ((mot64)(argv[4][5]) << 40);
  reg1 &= MASK1;

  reg2 = (mot64)(argv[4][5]) | ((mot64)(argv[4][6]) << 8) | ((mot64)(argv[4][7]) << 16) | ((mot64)(argv[4][8]) << 24) | ((mot64)(argv[4][9]) << 32) | ((mot64)(argv[4][10]) << 40);
  reg2 >>= 3;
  reg2 &= MASK2; 

  reg3 = (mot64)(argv[4][10]) | ((mot64)(argv[4][11]) << 8) | ((mot64)(argv[4][12]) << 16) | ((mot64)(argv[4][13]) << 24) | ((mot64)(argv[4][14]) << 32) | ((mot64)(argv[4][15]) << 40);
  reg3 >>= 4;
  reg3 &= MASK3;

  printf("Register initial state : %lx %lx %lx\n", reg1, reg2, reg3);

  /***************************************/
  /* Generation de la suite chiffante    */
  /***************************************/
  j = 0L;
  while(fscanf(fin,(argv[1][0] == 'e')?"%c":"%02X",&lettre), !feof(fin))
   {
    j++;
    outblock = 0;
    for(i = 0;i < 8;i++)
     {
      x1 = f1[(reg1 & 1) | ((reg2 & 1) << 1) | ((reg3 & 1) << 2)];
      x2 = f2[(reg1 & 1) | ((reg2 & 1) << 1) | ((reg3 & 1) << 2)];
      x3 = f3[(reg1 & 1) | ((reg2 & 1) << 1) | ((reg3 & 1) << 2)];
      outblock |= ((x1 ^ x2 ^ x3) << i);
      
      reb = motpar(reg1 & POLY1);
      reg1 >>=1;
      reg1 |= (reb << L1); 
      
      reb = motpar(reg2 & POLY2);
      reg2 >>=1;
      reg2 |= (reb << L2);

      reb = motpar(reg3 & POLY3);
      reg3 >>=1;
      reg3 |= (reb << L3); 
     }
    if(argv[1][0] == 'e') fprintf(fout,"%02X",lettre^outblock);
    else fprintf(fout,"%c",lettre^outblock);
   }
  printf("\n");

  fclose(fin);
  fclose(fout);
 }
