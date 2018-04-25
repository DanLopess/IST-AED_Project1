#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(){
  char command;
  char string[50];
  int linha = 0;

  scanf("%c*[^' ']", &command);

  if (command == 'w')
    scanf("%s", string);
  else
    scanf("%d", &linha);
  printf("%d %s", linha, string);
  return 0;
}

void printLines(unsigned int line){
  int aux_matrix[MAXELEMENTS],size=0;
  for (i = 0; i < lastElement; i++){
    if(matrix[i].line == line){
      aux_matrix[size] = matrix[i];
    }
  if (size){

  }
  else
    printf("empty line\n");
  }

  int not_zero = 0; /* Checks if all elements within the limits are zero*/

  if (line <= maxLine(matrix,0,lastElement) && line >= minLine(matrix,0,lastElement)){
    for (i = 0; i < lastElement; i++){ /* Verifies if there is at least one element different from elementZero*/
      if (matrix[i].line == line && matrix[i].value != elementZero ){
        not_zero = 1;
        break;
      }
    }
    if (not_zero){
      printLines_aux(matrix,0,lastElement,line, elementZero);
    }

    else /*If the line only has elementZero values, it is empty*/
      printf("empty line\n");
  }
  else
    printf("empty line\n");
}
