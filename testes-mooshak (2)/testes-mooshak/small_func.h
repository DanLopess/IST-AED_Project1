/********************************************************
Library designed by Daniel Lopes
April 25th '18
This library has been created in order to simplify
the main code by 'hiding' the small auxiliary functions
while leaving the main functions for the .c file

Code Subject: Sparse Matrices
**********************************************************/
unsigned long int  minLine(matrixElement *matrix, int inf_l, int sup_l){
  /*
 * Function: minLine
 * --------------------
 *  sweeps the vector and finds the lowest line
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: a line number
 */
  unsigned long int  minLine = matrix[0].line;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].line < minLine)
      minLine = matrix[i].line;
  return minLine;
}
unsigned long int  minColmn(matrixElement *matrix, int inf_l, int sup_l){
  /*
 * Function: minColmn
 * --------------------
 *  sweeps the vector and finds the lowest column
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: a column number
 */
  unsigned long int  minColmn = matrix[0].column;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].column < minColmn)
      minColmn = matrix[i].column;
  return minColmn;
}
unsigned long int  maxLine(matrixElement *matrix, int inf_l, int sup_l){
  /*
 * Function: maxLine
 * --------------------
 *  sweeps the vector and finds the highest line
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: a line number
 */
  unsigned long int  maxLine = matrix[0].line;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].line > maxLine)
      maxLine = matrix[i].line;
  return maxLine;
}
unsigned long int  maxColmn(matrixElement *matrix, int inf_l, int sup_l){
  /*
 * Function: maxColmn
 * --------------------
 *  sweeps the vector and finds the highest column
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: a column number
 */
  unsigned long int  maxColmn = matrix[0].column;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].column > maxColmn)
      maxColmn = matrix[i].column;
  return maxColmn;
}

void removeZeros(matrixElement *matrix, int inf_l, int sup_l){
  /*
 * Function: removeZeros
 * --------------------
 *  sweeps the vector and replaces the element Zero by the next one, reducing
 *  the size of the vector by one, done multiple times, as many times as the
 *  number of elements Zero
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: none
 */
  int i, f;
  for (i = inf_l; i <= sup_l; i++){
    if (matrix[i].value == elementZero){
      for (f = i+1; f <= sup_l; f++){ /*Replaces element by the next one*/
        matrix[f-1] = matrix[f];
      }
      i--; /*element has been replaced so i and superior limit are reduced by 1*/
      sup_l--;
      lastElement--; /*Accesses the global variable*/
    }
  }
}

int howToSort(){
  /*
 * Function: howToSort (auxiliary to sort)
 * --------------------
 *  functions reads input from stdin and decides whether to sort
 *  by column or line first.
 *  If '\n' was written, sorts by line first and returns 0
 *  If 'column' was written, sorts by column first and returns 1
 *  input: none
 *  returns: 0 or 1
 */
  char buffer[MAXFILENAME]; /*Longest word expected is "column" which has 6chars
                            but, for the sake of not having any overflow,
                            the maximum size allowed will be MAXFILENAME*/
  char c;
  while((c=getchar())==' ');
  if (c == '\n'){ /*Sort by lines (omitted parameter)*/
    return 0;
  }
  else{
    char aux_buffer[MAXFILENAME];
    strcpy(aux_buffer,"column");
    buffer[0] = c;
    scanf("%s", &buffer[1]);
    if (strcmp(buffer,aux_buffer) == 0) /*Sort by columns*/
      return 1;
    else{
      return 2; /* Any value different from 1 and 0 would suffice*/
                /* because only 1 and 0 are considered cases in the switch*/
    }
  }
}

void sort_lines(matrixElement *matrix, int  inf_l, int  sup_l){
  /*
 * Function: sort_lines (auxiliary function to sort)
 * --------------------
 *  sorts a certain vector of matrixElement type by lines
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: none
 */
  int i,j;
  for (i = inf_l+1; i < sup_l; i++) {
    matrixElement v = matrix[i];
    j = i-1;
    while ( j>=inf_l && v.line < matrix[j].line ) {
      matrix[j+1] = matrix[j];
      j--;
    }
    matrix[j+1] = v;
  }
}

void sort_columns(matrixElement *matrix, int  inf_l, int  sup_l){
  /*
 * Function: sort_columns (auxiliary function to sort)
 * --------------------
 *  sorts a certain vector of matrixElement type by columns
 *  input: *matrix (vector of type matrixElement),int inf_l, int sup_l
 *  returns: none
 */
  int i,j;
  for (i = inf_l+1; i < sup_l; i++) {
    matrixElement v = matrix[i];
    j = i-1;
    while ( j>=inf_l && v.column < matrix[j].column ) {
      matrix[j+1] = matrix[j];
      j--;
    }
    matrix[j+1] = v;
  }
}

double matrix_density(matrixElement *matrix, int lastElement){
  /*
 * Function: matrix_density
 * --------------------
 *  based on the maximum and minimum lines and columns and elements represented
 *  calculates the matrix density
 *  input: *matrix (vector of type matrixElement)
 *  returns: the matrix density (double)
 */
  int size = (maxLine(matrix,0,lastElement)- minLine(matrix,0,lastElement)+1) *
  (maxColmn(matrix,0,lastElement)-minColmn(matrix, 0,lastElement)+1); /* Finds out the matrix size */
  double density = (double)lastElement / size;
  return density;
}

/*---- Compression-specific functions ----*/

double line_density(matrixElement *matrix, unsigned long int  line){
  /*
 * Function: line_density
 * --------------------
 *  based on the maximum and minimum columns and elements represented
 *  calculates the line density
 *  input: *matrix (vector of type matrixElement), unsigned long int  line
 *  returns: the line density (double)
 */
  int elements=(maxColmn(matrix,0,lastElement)-minColmn(matrix,0,lastElement)+1);
  int nonZeroElements = 0, i;
  for (i = 0; i < lastElement; i++)
    if (matrix[i].line == line)
      nonZeroElements++;
  return (nonZeroElements/ (double) elements);
}

int buildAuxiliary(matrixElement *matrix, unsigned long int *linesByDensity,
                  int lastElement){
  /*
 * Function: buildAuxiliary
 * --------------------
 *  builds linesByDensity vector with the lines sorted by density and by lines
 *  for those with same density
 *  input: matrixElement *matrix, unsigned long int *linesByDensity,
 *   int lastElement
 *  returns: number of existing lines
 */
  int i,f;
  int linesCount = 0;
  /*Puts all lines on the vector linesByDensity*/
  for (i = 0; i < lastElement; i++){
    int proceed=0;
    for (f = 0; f < linesCount; f++)
      if(matrix[i].line == linesByDensity[f]){
        proceed = 1;
        break;
      }
    if (!proceed){
      linesByDensity[linesCount]=matrix[i].line;
      linesCount++;
    }
  }

  /*Does the sorting by density*/
  for (i = 1; i < linesCount; i++) {
    unsigned long int v = linesByDensity[i];
    f = i-1;
    while ( f>=0 && line_density(matrix,v)>=line_density(matrix,linesByDensity[f])){
      if(line_density(matrix,v)==line_density(matrix,linesByDensity[f])){
        if (linesByDensity[f] > linesByDensity[f+1]){
          linesByDensity[f+1] = linesByDensity[f];
          linesByDensity[f] = v;
        }
      }
      else{
        linesByDensity[f+1] = linesByDensity[f];
        linesByDensity[f] = v;
      }
      f--;
    }
  }
  return linesCount;
}

int testPlaceValues(matrixElement *matrix, double *value, int lastElement,
  unsigned long int sup_l,unsigned long int inf_l, int position,
  double *completeLine,unsigned long int line){
  /*
 * Function: testPlaceValues
 * --------------------
 *  based on the input given, this function will either TRY to compress the
 *  values and indexes of a line and returns 1 if it is possible or 0 if not
 *  input: matrixElement *matrix, double *value, int lastElement,
 * unsigned long int sup_l,unsigned long int inf_l,unsigned long int line,
 *  int position, double *completeLine
 *  returns: 1 or 0 (test)
 */
  int lineSize = sup_l - inf_l+1;
  unsigned long int f,j;
  int i;
  for (j=inf_l,f=0; f <= lineSize && j <= sup_l; f++){
    int added = 0;
    for (i = 0; i < lastElement; i++){
      if (matrix[i].line == line && matrix[i].column == j){
        completeLine[f] = matrix[i].value;
        added = 1;
        break;
      }
    }
    if (!added){
      completeLine[f] = elementZero;
    }
    j++; /*Controls the column number*/
  }

  for (f = 0 , i = position; i <= (position + lineSize-1); i++,f++)
    if (value[i] != elementZero && completeLine[f] != elementZero)
      return 0; /*Test failed*/

  return 1; /*Test passed*/
}

void compressedMatrix(double *value, unsigned long int *index, unsigned long int offset[][1],
                      int lastPos, matrixElement *matrix){
  /*
 * Function: compressedMatrix
 * --------------------
 *  prints the final compression vectors
 *  input: double *value, unsigned long int *index, unsigned long int offset[][1],
 *         int lastPos, matrixElement *matrix
 *  returns: none
 */
  unsigned long int inf_l = minLine(matrix,0,lastElement),
  sup_l = maxLine(matrix,0,lastElement); /*Offset limits*/
  int i;

  printf("value =");
  for (i = 0; i <= lastPos; i++)
    printf(" %.3f", value[i]);
  printf("\nindex =");
  for (i = 0; i <= lastPos; i++)
    printf(" %lu", index[i]);
  printf("\noffset =");
  for (i = inf_l; i <= sup_l; i++)
    printf(" %lu", offset[i][0]);
  printf("\n");
}
