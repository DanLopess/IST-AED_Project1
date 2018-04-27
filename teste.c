#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


/* Pre-processed constants and structures*/
#define MAXELEMENTS 10000 /* Maximum elements allowed in matrix*/
#define MAXFILENAME 80

typedef struct{
  unsigned int line, column;
  double value;
} matrixElement; /* matrix element represented by line, column and value */


/* Global Variables */
double elementZero = 0.000; /* Zero is initially represented by 0 */
int lastElement = 0; /* Must be global variable so it can be always altered */
char file_name[MAXFILENAME];

void sort_lines(matrixElement *matrix, unsigned int l_inf, unsigned int l_sup){
  int i,j;
  for (i = l_inf+1; i < l_sup; i++) {
    matrixElement v = matrix[i];
    j = i-1;
    while ( j>=l_inf && v.line < matrix[j].line ) {
      matrix[j+1] = matrix[j];
      j--;
    }
    matrix[j+1] = v;
  }
}

void sort_columns(matrixElement *matrix, unsigned int l_inf, unsigned int l_sup){
  int i,j;
  for (i = l_inf+1; i < l_sup; i++) {
    matrixElement v = matrix[i];
    j = i-1;
    while ( j>=l_inf && v.column < matrix[j].column ) {
      matrix[j+1] = matrix[j];
      j--;
    }
    matrix[j+1] = v;
  }
}

void removeZeros(matrixElement *matrix, int l_inf, int l_sup){
  int i, f;
  for (i = l_inf; i < l_sup; i++){
    if (matrix[i].value == elementZero){
      for (f = i; f < l_sup-1; f++){ /*Replaces element by the next one*/
        matrix[f] = matrix[f+1];
      }
    }
  }
  lastElement--;
}

void addElement(matrixElement *matrix){
  matrixElement addNewElement;
  int added = 0, i;
  scanf("%u%u%lf", &addNewElement.line, &addNewElement.column, &addNewElement.value);
  for (i = 0; i < lastElement; i++){
    if (addNewElement.line == matrix[i].line && addNewElement.column == matrix[i].column){ /*If coordinate already has a value*/
        if (addNewElement.value != elementZero){
          matrix[i] = addNewElement;
          added = 1;
        }
        else
          removeZeros(matrix,i,lastElement); /* If changed to zero an element, remove that element*/
        break;
    }
  }
  if (!added && addNewElement.value != elementZero){ /*Add new element different from zero*/
    matrix[lastElement] = addNewElement;
    lastElement++;
  }
}

void printElements(matrixElement *matrix){
  if (lastElement == 0)
    printf("empty matrix\n");
  else{
    int i;
    for (i = 0; i < lastElement; i++)
      printf("[%d;%d]=%.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
  }
}


int main(){
  matrixElement matrix[MAXELEMENTS];
  char command;
  int end_program;

  do{
    scanf("%c", &command); /*Reads first character */
    if (command != 'q'){
      switch (command){
        case 'a':{
          addElement(matrix);
          break;
        }
        case 'p':{
          printElements(matrix);
          break;
        }
        case 'o':{
        unsigned int i, f, l_sup;

        sort_lines(matrix, 0, lastElement); /*Sorted by lines*/
        printElements(matrix);
        for (i=0;i<lastElement;i++){
          for (f = i; matrix[f].line == matrix[i].line; f++) l_sup = f; /*Finds last position of same line*/
          sort_columns(matrix,i,l_sup);
          i = l_sup;
        }
        break;
        }

      }
    }
    else end_program = 1;
  } while(end_program == 0);
  return 0;
}
