#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "encrypt.h"

int main(int argc, char **argv) {

unsigned char      destmp[8],
                   desptx[8],
                   desctx[8],
                   deskey[8];

int                i;

/*****************************************************************************
*                                                                            *
*  DES-TOOLS
*
*  -r     Number of rounds
*  -z     Use zeroed key
*  -n     No permutations
*  -gfni  Use Galois Field New Instruction
*  -a     Analyze (determine linear approximation)
*  -v     Verbose
*                                                                            *
*****************************************************************************/

static struct _CMD_OPTIONS {
	int f_ROUNDS           ;
	int f_ZEROED_KEY;      ;
	int f_NO_PERMUTATIONS  ;
	int f_USE_GFNI         ;
	int f_ANALYZE          ;
	int f_VERBOSE          ;
} CMD_OPTIONS; 

CMD_OPTIONS.f_ROUNDS           = false;
CMD_OPTIONS.f_ZEROED_KEY       = false;
CMD_OPTIONS.f_NO_PERMUTATIONS  = false;
CMD_OPTIONS.f_USE_GFNI         = false;
CMD_OPTIONS.f_ANALYZE          = false;
CMD_OPTIONS.f_VERBOSE          = false;

destmp[0] = 0xa9;
destmp[1] = 0x10;
destmp[2] = 0x11;
destmp[3] = 0x38;
destmp[4] = 0x93;
destmp[5] = 0xca;
destmp[6] = 0xb4;
destmp[7] = 0xa1;

deskey[0] = 0x01;
deskey[1] = 0x1f;
deskey[2] = 0x01;
deskey[3] = 0x1f;
deskey[4] = 0x01;
deskey[5] = 0x0e;
deskey[6] = 0x01;
deskey[7] = 0x0e;

fprintf(stdout, "DES-TOOLS\n");

   int opt; 

   // put ':' in the starting of the 
   // string so that program can  
   //distinguish between '?' and ':'  
   while((opt = getopt(argc, argv, ':if:lrx')) != -1)  
   {  
      switch(opt)  
      {  
         case 'r':  
	       CMD_OPTIONS.f_ROUNDS = true;
               printf('rounds: %c\n', opt);  
               break;
         case 'z':
	       CMD_OPTIONS.f_ZEROED_KEY = true;        
               printf('zeroed key: %c\n', opt);  
               break;  
         case 'n':  
	       CMD_OPTIONS.f_NO_PERMUTATIONS = true;
               printf('no permutations: %c\n', opt);  
               break;  
         case 'gfni':  
               printf('use GFNI: %s\n', opt);  
               break;
         case 'a':  
               printf('Apply Linear Analysis : %s\n', opt);  
               break;
         case 'v':  
               printf('Verbose: %s\n', opt);  
               break;  
         case ':':  
               printf('option needs a value\n');  
               break;  
         case '?':  
               printf('unknown option: %c\n', opt); 
               break;  
      }  
   }  

   // optind is for the extra arguments 
   // which are not parsed 
   for(int optind = 0; optind < argc; optind++){      
      printf('extra arguments: %s\n', argv[optind]);  
   } 


fprintf(stdout, "Using key: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   deskey[0], deskey[1], deskey[2], deskey[3], deskey[4], deskey[5],
   deskey[6], deskey[7]);

des_encipher(destmp, desctx, deskey);
 
fprintf(stdout, "plaintext: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   destmp[0], destmp[1], destmp[2], destmp[3], destmp[4], destmp[5],
   destmp[6], destmp[7]);

fprintf(stdout, "ciphertext: %02x %02x %02x %02x %02x %02x %02x %02x\n",
   desctx[0], desctx[1], desctx[2], desctx[3], desctx[4], desctx[5],
   desctx[6], desctx[7]);

return 0;

}
