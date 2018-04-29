/************
*************
April 25th '18

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
#define MAXFILENAME 80 /*Maximum size for file name*/

typedef struct{
  unsigned long int  line, column;
  double value;
} matrixElement; /* matrix element represented by line, column and value */


/* Global Variables */
double elementZero = 0.000; /* Zero is initially represented by 0 */
int lastElement = 0; /* Must be global variable so it can be always altered */
char file_name[MAXFILENAME]; /* Global variable that stores the file name*/

/* Function Declaration/Prototype */
#include "small_func.h" /* Library that contains auxiliary functions */
void executeCommand(char command, matrixElement *matrix);
void addElement(matrixElement *matrix);
void printElements(matrixElement *matrix);
void printDetails(matrixElement *matrix);
void printLines(matrixElement *matrix);
void printColumns(matrixElement *matrix);
void sort(matrixElement *matrix);
void save_matrix(matrixElement *matrix);
void compress_matrix(matrixElement *matrix);


/* Main Function */
int main(int argc, char *argv[]){
  int end_program = 0;
  char command;
  matrixElement matrix[MAXELEMENTS];

  if (argc == 2){ /*If there was a matrix input through a file*/
    FILE *fptr;
    int i=0;

    strcpy(file_name,argv[1]);

    fptr = fopen(file_name, "r");

    fptr = fopen(file_name, "r");
    if(fptr != NULL)
      for (i=0; !feof(fptr);i++)
        if (fscanf(fptr,"%lu %lu %lf",&matrix[i].line,&matrix[i].column,&matrix[i].value)==3)
          lastElement++;
    fclose(fptr);
  }

  do{
    scanf("%c", &command); /*Reads first character */
    if (command != 'q'){
      executeCommand(command ,matrix);
    }
    else end_program = 1;
  } while(end_program == 0);

  return 0;
}


/* Function Implementation */
void executeCommand(char command, matrixElement *matrix){
  /*
 * Function:  executeCommand
 * --------------------
 *  Based on the command read in the main, this function will call
 *  the specific function that execute a certain action
 *  input: char command and matrixElement *matrix (vector of type matrixElement)
 *  returns: none
 */
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
      printLines(matrix);
      break;
    }
    case 'c':{
      printColumns(matrix);
      break;
    }
    case 'o':{
      sort(matrix);
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

void addElement(matrixElement *matrix){
  /*
 * Function:  addElement
 * --------------------
 *  Adds to the vector a new element on the 'lastElement' position
 *  input: matrixElement *matrix (vector of type matrixElement)
 *  returns: none
 */
  matrixElement addNewElement;
  int added = 0, i; /*Added controls if element has been altered or added*/
  scanf("%lu%lu%lf", &addNewElement.line, &addNewElement.column,
        &addNewElement.value);
  for (i = 0; i < lastElement; i++){
    if (addNewElement.line == matrix[i].line &&
        addNewElement.column == matrix[i].column){
      matrix[i] = addNewElement;
      /* If an element was changed to zero, remove that element*/
      if (matrix[i].value == elementZero){
        removeZeros(matrix,i,lastElement-1);
        break;
      }
      /*Else add 1 to the control variable*/
      added = 1;
      break;
    }
  }

  if (!added && addNewElement.value != elementZero){
    matrix[lastElement] = addNewElement; /*Add new element different from zero*/
    lastElement++;
  }
}

void printElements(matrixElement *matrix){
  /*
 * Function:  printElements
 * --------------------
 *  Prints to the stdout all the elements in the vector matrix
 *  input: matrixElement *matrix (vector of type matrixElement)
 *  returns: none
 */
  if (lastElement == 0)
    printf("empty matrix\n");
  else{
    int i;
    for (i = 0; i < lastElement; i++)
      printf("[%lu;%lu]=%.3f\n",matrix[i].line,matrix[i].column,matrix[i].value);
  }
}

void printDetails(matrixElement *matrix){
  /*
 * Function:  printDetails
 * --------------------
 *  Prints to the stdout all the details of a certain matrix
 *  i.e. the lines and columns limits as well as the matrix density
 *  input: matrixElement *matrix (vector of type matrixElement)
 *  returns: none
 */
  int superior_line = maxLine(matrix,0,lastElement),
  inferior_line = minLine(matrix,0,lastElement),
  superior_colmn = maxColmn(matrix,0,lastElement),
  inferior_colmn = minColmn(matrix, 0,lastElement);
  int size = (superior_line-inferior_line+1)*(superior_colmn-inferior_colmn+1);
  if (lastElement == 0)
    printf("empty matrix\n");
  else
    printf("[%d %d] [%d %d] %d / %d = %.3f%%\n", inferior_line, inferior_colmn,
    superior_line,superior_colmn,lastElement,size,matrix_density(matrix,lastElement)*100);
}

void printLines(matrixElement *matrix){
  /*
 * Function:  printLines
 * --------------------
 *  Prints to the stdout all the columns of a certain line
 *  input: *matrix (vector of type matrixElement),unsigned long int line
 *  returns: none
 */
  matrixElement aux_matrix[MAXELEMENTS];
  unsigned long int  i,f;
  int size=0,found_value;
  unsigned long int  line;

  scanf("%lu", &line);

  for (i = 0; i < lastElement; i++){
    if(matrix[i].line == line){
      aux_matrix[size] = matrix[i];
      size++;
    }
  }
  if (size > 0){
    for(i=minColmn(matrix,0,lastElement);i<=maxColmn(matrix,0,lastElement);i++){
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

void printColumns(matrixElement *matrix){
  /*
 * Function:  printColumns
 * --------------------
 *  Prints to the stdout all the lines of a certain column
 *  input: *matrix (vector of type matrixElement),unsigned long int column
 *  returns: none
 */
    matrixElement aux_matrix[MAXELEMENTS];
    unsigned long int  i, f;
    int size=0,found_value;
    unsigned long int  column;

    scanf("%lu", &column);

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
            printf("[%lu;%lu]=%.3f\n", i , column, aux_matrix[f].value);
            found_value = 1;
            break;
          }
        if(found_value == 0)
          printf("[%lu;%lu]=%.3f\n", i, column ,elementZero);
      }
    }
    else
      printf("empty column\n");

}

void sort(matrixElement *matrix){
    /*
   * Function: sort
   * --------------------
   *  sorts a certain vector of matrixElement type by columns or by lines
   *  if lineOrColumn == 0, sorts by line first, if lineOrColumn == 1, by column first
   *  input: *matrix (vector of type matrixElement),int lineOrColumn
   *  returns: none
   */
  int  i, f, sup_l,lineOrColumn;
  lineOrColumn = howToSort();

  switch(lineOrColumn){
    case 0:{ /*Sort by lines first*/
      sort_lines(matrix, 0, lastElement); /*Sorted by lines*/
/*--- Find the limits that contain the same line and sort it by columns ------*/
      for (i=0,sup_l = i;i<lastElement;i++){
        unsigned long int  line = matrix[i].line;
        for (f = i; matrix[f].line == line; f++)
          sup_l = f+1; /*Finds last position of same line*/
        sort_columns(matrix,i,sup_l);
        i = sup_l; /*i moves to the last position of the considered line*/
        /*and then the cycle will increment it by 1*/
      }
      break;
    }
    case 1:{  /*Sort by columns first*/
      sort_columns(matrix, 0, lastElement); /*Sorted by columns*/
/*--- Find the limits that contain the same column and sort it by lines ------*/
      for (i=0,sup_l = i;i<lastElement;i++){
        unsigned long int  column = matrix[i].column;
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
  /*
 * Function:  save_matrix
 * --------------------
 *  saves to a certain file (file_name) the whole matrix
 *  input: *matrix (vector of type matrixElement)
 *  returns: none
 */
    FILE *fptr;
    int i;
    char buffer[MAXFILENAME], c;

    while((c=getchar())==' ');
    if (c != '\n'){
      buffer[0] = c;
      scanf ("%[^\n]%*c", &buffer[1]); /*Allows file name to have spaces*/
      strcpy(file_name,buffer);
    } /*Reads the file name*/

    fptr = fopen(file_name, "w");
    if(fptr == NULL)
        return;
    for(i = 0; i < lastElement; i++){ /* Prints into file */
      fprintf(fptr,"%lu %lu %.3f\n", matrix[i].line,
      matrix[i].column, matrix[i].value);
    }
    fclose(fptr);
}
