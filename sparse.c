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


/* Pre-processed constants and structures*/
#define MAXELEMENTS 10000 /* Maximum elements allowed in matrix*/

typedef struct{
  unsigned int line, column;
  double value;
} matrixElement; /* matrix element represented by line, column and value */


/* Global Variables */
double elementZero = 0.000; /* Zero is initially represented by 0 */
int lastElement = 0; /* Counting variable for matrix size */
int i; /* used in for cycles  */
matrixElement matrix[MAXELEMENTS];

/* Function Declaration/Prototype */
void addElement();
void printElements();
void printDetails();
void printLines(unsigned int line);
void printColumns(unsigned int column);
void sort(matrixElement *matrix);
void elementZero(double element);
void save_matrix(matrixElement *matrix);
void compress_matrix(matrixElement *matrix);

/* Main Function */
int main(){
  int end_program = 0;
  char command;

  do{
    scanf("%c*[' ']", &command); /*Reads first character until it finds a blank space*/
    if (command != 'q'){
      switch (command){
        case 'a':{
          addElement();
          break;
        }
        case 'p':{
          printElements(); /* lastElement passed by reference so it can't be modified*/
          break;
        }
        case 'i':{
          printDetails();
          break;
        }
        case 'l':{
          unsigned int line;
          scanf("%u*['\n']", &line);
          printLines(line);
          break;
        }
        case 'c':{
          unsigned int column;
          scanf("%u*['\n']", &column);
          printColumns(column);
          break;
        }
      }
    }
    else end_program = 1;
  } while(end_program == 0);


  return 0;
}


/* Function Implementation */
#include "small_func.h" /* Library that contains auxiliary functions */

void addElement(){
  matrixElement addNewElement;
  int added = 0;
  scanf("%u%u%lf*['\n']", &addNewElement.line, &addNewElement.column, &addNewElement.value);
  for (i = 0; i < lastElement; i++){
    if (addNewElement.line == matrix[i].line && addNewElement.column == matrix[i].column){
        matrix[i] = addNewElement;
        added = 1;
        break;
    }
  }
  if (!added){
    matrix[lastElement] = addNewElement;
    lastElement++;
  }
}

void printElements(){
  if (lastElement == 0)
    printf("empty matrix\n");
  else
    for (i = lastElement-1; i >= 0; i--)
      if (matrix[i].value != elementZero)
        printf("[%d;%d]=%.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
}

void printDetails(){
  unsigned int superior_line = maxLine(matrix,0,lastElement), superior_colmn = maxColmn(matrix,0,lastElement);
  unsigned int inferior_line = minLine(matrix,0,lastElement), inferior_colmn = minColmn(matrix, 0,lastElement);
  int size = (superior_line-inferior_line+1) * (superior_colmn-inferior_colmn+1); /* Finds out the matrix size */
  double ratio = (double)lastElement / size;

  if (lastElement == 0)
    printf("empty matrix\n");
  else
    printf("[%d %d] [%d %d] %d / %d = %.3f%% \n", inferior_line, inferior_colmn,
    superior_line,superior_colmn, lastElement, size, ratio*100);
}

void printLines(unsigned int line){
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
      printf("empty line");
  }
  else
    printf("empty line");
}

void printColumns(unsigned int column){
  int not_zero = 0; /* Checks if all elements within the limits are zero*/

  if (column <= maxColmn(matrix,0,lastElement) && column >= minColmn(matrix,0,lastElement)){
    for (i = 0; i < lastElement; i++){ /* Verifies if there is at least one element different from elementZero*/
      if (matrix[i].column == column && matrix[i].value != elementZero ){
        not_zero = 1;
        break;
      }
    }
    if (not_zero){
      printColumns_aux(matrix,0,lastElement,column, elementZero);
    }

    else /*If the line only has elementZero values, it is empty*/
      printf("empty column");
  }
  else
    printf("empty column");
}
