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
#define MAXFILENAME 80

typedef struct{
  unsigned int line, column;
  double value;
} matrixElement; /* matrix element represented by line, column and value */


/* Global Variables */
double elementZero = 0.000; /* Zero is initially represented by 0 */
int lastElement = 0; /* Must be global variable so it can be always altered */
char file_name[MAXFILENAME];

/* Function Declaration/Prototype */
void addElement(matrixElement *matrix);
void printElements(matrixElement *matrix);
void printDetails(matrixElement *matrix);
void printLines(matrixElement *matrix, unsigned int line);
void printColumns(matrixElement *matrix, unsigned int column);
int cmpfunc_column (const void *a, const void *b);
int cmpfunc_line (const void *a, const void *b);
void sort(matrixElement *matrix, int lineOrColumn);
void save_matrix(matrixElement *matrix, char *file_name);
/*void compress_matrix(matrixElement *matrix);*/

/* Main Function */
int main(){
  int end_program = 0;
  char command;
  matrixElement matrix[MAXELEMENTS];

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
        case 'i':{
          printDetails(matrix);
          break;
        }
        case 'l':{
          unsigned int line;
          scanf("%u", &line);
          printLines(matrix, line);
          break;
        }
        case 'c':{
          unsigned int column;
          scanf("%u", &column);
          printColumns(matrix, column);
          break;
        }
        case 'o':{
          char readLine[10];
          scanf("%s", readLine);
          if (readLine[1] == '\0') /*If reads "\n\0" then it's lines first*/
            sort(matrix,0);
          else if(strcmp(readLine,"column") == 0)
            sort(matrix,1);
          break;
        }
        case 'z':{
          double element;
          scanf("%lf*['\n']", &element);
          elementZero = element;
          break;
        }
        case 'w':{
          char c;
          if (strlen(file_name) >= 1 && (c = getchar()) == '\n'){
            save_matrix(matrix, file_name);
          }
          else{
            scanf("%s", file_name);
            save_matrix(matrix, file_name);
          }
          break;
        }
        case 's':{

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
          removesZeros(matrix,i,lastElement);
        break;
    }
  }
  if (!added && addNewElement.value != elementZero){
    matrix[lastElement] = addNewElement;
    lastElement++;
  }
}

void printElements(matrixElement *matrix){
  if (lastElement == 0)
    printf("empty matrix\n");
  else
    int i;
    for (i = lastElement-1; i >= 0; i--)
      printf("[%d;%d]=%.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
}

void printDetails(matrixElement *matrix){
  int size = (superior_line-inferior_line+1) * (superior_colmn-inferior_colmn+1); /* Finds out the matrix size */
  double ratio = (double)lastElement / size;

  if (lastElement == 0)
    printf("empty matrix\n");
  else
    printf("[%d %d] [%d %d] %d / %d = %.3f%% \n", minLine(matrix,0,lastElement), minColmn(matrix, 0,lastElement),
    maxLine(matrix,0,lastElement),maxColmn(matrix,0,lastElement), lastElement, size, ratio*100);
}

void printLines(matrixElement *matrix, unsigned int line){
  matrixElement aux_matrix[MAXELEMENTS];
  unsigned int i,f,size=0,found_value;

  for (i = 0; i < lastElement; i++){
    if(matrix[i].line == line && matrix[i].value != elementZero){
      aux_matrix[size] = matrix[i];
      size++;
    }
  }
  if (size > 0){
    for (i = minColmn(matrix,0,lastElement); i <= maxColmn(matrix,0,lastElement); i++){
      found_value = 0;
      for (f = 0; f < size; f++)
        if (aux_matrix[f].column == i){
          printf(" %.3f", aux_matrix[f].value);
          found_value = 1;
          break;
        }
      if(found_value == 0)
        printf(" %.3f", elementZero);
    }
  }
  else
    printf("empty line");
  printf("\n");
}

void printColumns(matrixElement *matrix, unsigned int column){
    matrixElement aux_matrix[MAXELEMENTS];
    unsigned int i, f,size=0,found_value;

    for (i = 0; i < lastElement; i++){
      if(matrix[i].column == column && matrix[i].value != elementZero){
        aux_matrix[size] = matrix[i];
        size++;
      }
    }
    if (size > 0){
      for (i = minLine(matrix,0,lastElement); i <= maxLine(matrix,0,lastElement); i++){
        found_value = 0;
        for (f = 0; f < size; f++)
          if (aux_matrix[f].line == i){
            printf(" %.3f", aux_matrix[f].value);
            found_value = 1;
            break;
          }
        if(found_value == 0)
          printf(" %.3f", elementZero);
      }
    }
    else
      printf("empty column");
    printf("\n");
}


void sort(matrixElement *matrix, int lineOrColumn){ /*0 - line, 1 - column*/
  switch(lineOrColumn){
    case 0:{
        qsort(matrix, lastElement, sizeof(matrixElement), cmpfunc_line);
        break;
    }
    case 1:{
        qsort(matrix, lastElement, sizeof(matrixElement), cmpfunc_column);
        break;
    }
  }

}

int cmpfunc_line (const void *a, const void *b) {
   return (strcmp(((matrixElement * )a)->line, ((matrixElement *)b)->line));
}
int cmpfunc_column (const void *a, const void *b) {
   return (strcmp(((matrixElement * )a)->column, ((matrixElement *)b)->column));
}

void save_matrix(matrixElement *matrix, char *file_name){
    FILE *fptr;
    int i;

    fptr = fopen(file_name, "w");
    if(fptr == NULL) /*if file does not exist, create it*/
        freopen(file_name, "w", fptr);
    for(i = 0; i < lastElement; i++){
      fprintf(fptr,"%u %u %.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
    }
    fclose(fptr);
}
