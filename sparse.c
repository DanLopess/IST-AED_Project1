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
int auxiliarySize = 0; /*Used in compression*/

/* Function Declaration/Prototype */
#include "small_func.h" /* Library that contains auxiliary functions */
void addElement(matrixElement *matrix);
void printElements(matrixElement *matrix);
void printDetails(matrixElement *matrix);
void printLines(matrixElement *matrix, unsigned int line);
void printColumns(matrixElement *matrix, unsigned int column);
void sort(matrixElement *matrix, int lineOrColumn);
void save_matrix(matrixElement *matrix);
/*void compress_matrix(matrixElement *matrix);*/

/* Main Function */
int main(int argc, char *argv[]){
  int end_program = 0;
  char command;
  matrixElement matrix[MAXELEMENTS];

  if (argc == 2){ /*If there is a matrix input*/
    FILE *fptr;
    int i=0;

    strcpy(file_name,argv[1]);

    fptr = fopen(file_name, "r");

    fptr = fopen(file_name, "r");
    if(fptr != NULL)
      for (i=0; !feof(fptr);i++)
        if (fscanf(fptr,"%u %u %lf",&matrix[i].line,&matrix[i].column,&matrix[i].value)==3)
          lastElement++;
    fclose(fptr);
  }

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
          char buffer[MAXFILENAME]; /*Longest word expected is "column" which has 6 characters
                                    but, for the sake of not having any overflow,
                                    the maximum size allowed will be MAXFILENAME*/
          char c;
          while((c=getchar())==' ');
          if (c == '\n') /*Sort by lines (omitted parameter)*/
            sort(matrix,0);
          else{
            char aux_buffer[MAXFILENAME];

            strcpy(aux_buffer,"column");
            buffer[0] = c;
            scanf("%s", &buffer[1]);
            if (strcmp(buffer,aux_buffer) == 0) /*Sort by columns*/
              sort(matrix,1);
          }
          break;
        }
        case 'z':{
          double element;
          scanf("%lf", &element);
          elementZero = element;
          if (lastElement > 0) /*Only need to call if there's an element in matrix*/
            removeZeros(matrix,0,lastElement-1);
          break;
        }
        case 'w':{
          save_matrix(matrix);
          break;
        }
        case 's':{
          /*compress_matrix(matrix);*/
          break;
        }
      }
    }
    else end_program = 1;
  } while(end_program == 0);

  return 0;
}

/* Function Implementation */

void addElement(matrixElement *matrix){
  matrixElement addNewElement;
  int added = 0, i; /*Added controls if element has been altered or added*/
  scanf("%u%u%lf", &addNewElement.line, &addNewElement.column, &addNewElement.value);
  for (i = 0; i < lastElement; i++){
    if (addNewElement.line == matrix[i].line && addNewElement.column == matrix[i].column){
      if (addNewElement.value == elementZero){
        matrix[i] = addNewElement;
        removeZeros(matrix,i,lastElement-1);
        break;
      } /* If changed to zero an element, remove that element*/
      matrix[i] = addNewElement;
      added = 1;
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

void printDetails(matrixElement *matrix){
  int superior_line = maxLine(matrix,0,lastElement), inferior_line = minLine(matrix,0,lastElement);
  int superior_colmn = maxColmn(matrix,0,lastElement), inferior_colmn = minColmn(matrix, 0,lastElement);
  int size = (superior_line- inferior_line+1) * (superior_colmn-inferior_colmn+1);
  if (lastElement == 0)
    printf("empty matrix\n");
  else
    printf("[%d %d] [%d %d] %d / %d = %.3f%%\n", inferior_line, inferior_colmn,
    superior_line,superior_colmn, lastElement, size, matrix_density(matrix)*100);
}

void printLines(matrixElement *matrix, unsigned int line){
  matrixElement aux_matrix[MAXELEMENTS];
  unsigned int i,f,size=0,found_value;

  for (i = 0; i < lastElement; i++){
    if(matrix[i].line == line){
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
      if(matrix[i].column == column){
        aux_matrix[size] = matrix[i];
        size++;
      }
    }
    if (size > 0){
      for (i = minLine(matrix,0,lastElement); i <= maxLine(matrix,0,lastElement); i++){
        found_value = 0;
        for (f = 0; f < size; f++)
          if (aux_matrix[f].line == i){
            printf("[%u;%u]=%.3f\n", i , column, aux_matrix[f].value);
            found_value = 1;
            break;
          }
        if(found_value == 0)
          printf("[%u;%u]=%.3f\n", i, column ,elementZero);
      }
    }
    else
      printf("empty column\n");

}

void sort(matrixElement *matrix, int lineOrColumn){ /*0 - line, 1 - column*/
  switch(lineOrColumn){
    case 0:{ /*Sort by lines first*/
      unsigned int i, f, sup_l;

      sort_lines(matrix, 0, lastElement); /*Sorted by lines*/

      /*------- Find the limits that contain the same line and sort it by columns ------*/
      for (i=0,sup_l = i;i<lastElement;i++){
        unsigned int line = matrix[i].line;
        for (f = i; matrix[f].line == line; f++)
          sup_l = f+1; /*Finds last position of same line*/
        sort_columns(matrix,i,sup_l);
        i = sup_l; /*i moves to the last position of the considered line*/
        /*and then the cycle will increment it by 1*/
      }
      break;
    }
    case 1:{  /*Sort by columns first*/
      unsigned int i, f, sup_l;

      sort_columns(matrix, 0, lastElement); /*Sorted by columns*/

      /*------- Find the limits that contain the same column and sort it by lines ------*/
      for (i=0,sup_l = i;i<lastElement;i++){
        unsigned int column = matrix[i].column;
        for (f = i; matrix[f].column == column; f++)
          sup_l = f+1; /*Finds last position of same column*/
        sort_lines(matrix,i,sup_l);
        i = sup_l; /*i moves to the last position of the considered column*/
        /*and then the cycle will increment it by 1*/
      }
      break;
    }
  }
}

void save_matrix(matrixElement *matrix){
    FILE *fptr;
    int i;
    char buffer[MAXFILENAME], c;

    while((c=getchar())==' ');
    if (c != '\n'){
      buffer[0] = c;
      scanf("%s", &buffer[1]);
      strcpy(file_name,buffer);
    }

    fptr = fopen(file_name, "w");
    if(fptr == NULL)
        return;
    for(i = 0; i < lastElement; i++){
      fprintf(fptr,"%u %u %.3f\n", matrix[i].line, matrix[i].column, matrix[i].value);
    }
    fclose(fptr);
}
