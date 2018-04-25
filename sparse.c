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

/* Function Declaration/Prototype */
void addElement(matrixElement *matrix);
void printElements(matrixElement *matrix);
void printDetails(matrixElement *matrix);
void printLines(matrixElement *matrix, unsigned int line);
void printColumns(matrixElement *matrix, unsigned int column);
/*void sort(matrixElement *matrix);*/
void save_matrix(matrixElement *matrix, char *file_name);
/*void compress_matrix(matrixElement *matrix);*/

/* Main Function */
int main(){
  int end_program = 0;
  char command, file_name[MAXFILENAME];
  matrixElement matrix[MAXELEMENTS];

  do{
    scanf("%c*[' ']", &command); /*Reads first character until it finds a blank space*/
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

void printElements(matrixElement *matrix){
  int i;
  if (lastElement == 0)
    printf("empty matrix\n");
  else
    for (i = lastElement-1; i >= 0; i--)
      if (matrix[i].value != elementZero)
        printf("[%d;%d]=%.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
}

void printDetails(matrixElement *matrix){
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

void printLines(matrixElement *matrix, unsigned int line){
  matrixElement aux_matrix[MAXELEMENTS];
  unsigned int i,f,size=0,found_value;

  for (i = 0; i < lastElement; i++){
    if(matrix[i].line == line && matrix[i].value != elementZero){
      aux_matrix[size] = matrix[i];
      /*printf("Elemento adicionado: Linha %d Coluna %d Valor %.3f", aux_matrix[size].line, aux_matrix[size].column, aux_matrix[size].value);
      */size++;
    }
  }
  if (size > 0){
    for (i = minColmn(aux_matrix,0,size); i <= maxColmn(aux_matrix,0,size); i++){
      found_value = 0;
      for (f = 0; f < size; f++)
        if (aux_matrix[f].column == i){
          printf("%.3f ", aux_matrix[f].value);
          found_value = 1;
          break;
        }
      if(found_value == 0)
        printf("%.3f ", elementZero);
    }
  }
  else
    printf("empty line\n");
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
      for (i = minLine(aux_matrix,0,size); i <= maxLine(aux_matrix,0,size); i++){
        found_value = 0;
        for (f = 0; f < size; f++)
          if (aux_matrix[f].line == i){
            printf("%.3f ", aux_matrix[f].value);
            found_value = 1;
            break;
          }
        if(found_value == 0)
          printf("%.3f ", elementZero);
      }
    }
    else
      printf("empty column\n");
    printf("\n");
}

/*
int cmpfunc_line (const void *a, const void *b) {
   return (strcmp(((matrixElement * )a)->line, ((matrixElement *)b)->line));
}
void sort_by_line(matrixElement *matrix, int lastElement){
  qsort(matrix, lastElement, sizeof(matrixElement), cmpfunc_line);
}*/

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
