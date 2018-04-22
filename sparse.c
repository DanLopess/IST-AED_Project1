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

/* Pre-processed constants and structures*/
#define MAXELEMENTS 10000 /* Maximum elements allowed in matrix*/

typedef struct{
  unsigned int line, column;
  double value;
} matrixElement; /* a matrix element e represented by line, column and value */

/* Global Variables */
matrixElement matrix[MAXELEMENTS];
double elementZero = 0.000; /* Zero is initially represented by 0 */
int matrixSize = 0; /* Counting variable for matrix size */
int i; /* used in for cycles  */

/* Function Declaration/Prototype */
void printElements(matrixElement *matrix);
void printDetails(matrixElement *matrix);

/* Main Function */
int main(){
  int end_program = 0;
  char command;

  do{
    scanf("%c*[' ']", &command); /*Reads first character until it finds a blank space*/
    if (command != 'q'){
      switch (command){
        case 'a':{
          matrixElement addNewElement;
          scanf("%u%u%lf*['\n']", &addNewElement.line, &addNewElement.column, &addNewElement.value);
          matrix[matrixSize] = addNewElement;
          matrixSize++;
          break;
        }
        case 'p':{
          printElements(matrix);
          break;
        }
        case 'i':{
          printDetails(matrix);
          break;
        }
      }
    }
    else end_program = 1;
  } while(end_program == 0);


  return 0;
}


/* Function Implementation */
void printElements(matrixElement *matrix){
  if (matrixSize == 0)
    printf("empty matrix\n");
  else
    for (i = 0; i < matrixSize; i++)
      if (matrix[i].value != elementZero)
        printf("[%d;%d]=%.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
}

void printDetails(matrixElement *matrix){
  if (matrixSize == 0)
    printf("empty matrix\n");
  else
}
