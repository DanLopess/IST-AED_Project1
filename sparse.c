/************
*************
April 15th '18

All Rights Reserved © Daniel Lopes

Code Subject: Sparse Matrices
*************
*************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "small_func.h"

/* Pre-processed constants */
#define MAXCHARS 100

/* Global Variables */

/* Function Declaration/Prototype */


/* Main Function */
int main(){
  char read_line[MAXCHARS];

  while(menu(), fgets(read_line, MAXCHARS, stdin), read_line[0] != 'q'){ /* Usar scanf ler varias variaveis */
    switch (read_line[0]) {
      case 'a':{

        break;
      }
      case 2:{

        break;
      }
      case 3:{

        break;
      }

      default:{
        printf("Unknown Answer.\n");
        break;
      }
    }
  }

  return 0;
}


/* Function Implementation */

void menu(){ /* Maybe there's no need for menu - check it */
  printf("****SPARCE MATRICES****\n"
"1 - Inserir novo livro\n2 - Listar livros\n"
"3 - Procurar livro por isbn\n"
"4 - Procurar livro por título\n"
"5 - Alterar título do livro\n"
"6 - Apagar livro pelo isbn \n"
"7 - Registar data de empréstimo de um livro pelo isbn \n"
"8 - Registar data de retorno de um livro pelo isbn \n"
"9 - Ordenar livros por título \n"
"10 - Guardar livros em ficheiro \n0 - Sair \n"
"************************* \n");
}

nice
