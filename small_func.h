/********************************************************
Library designed by Daniel Lopes

This library has been created in order to simplify
the main code by 'hiding' the small auxiliary functions
while leaving the big functions for the main code

Code Subject: Sparse Matrices
**********************************************************/
unsigned int minLine(matrixElement *matrix, int inf_l, int sup_l){
  unsigned int minLine = matrix[0].line;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].line < minLine)
      minLine = matrix[i].line;
  return minLine;
}
unsigned int minColmn(matrixElement *matrix, int inf_l, int sup_l){
  unsigned int minColmn = matrix[0].column;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].column < minColmn)
      minColmn = matrix[i].column;
  return minColmn;
}
unsigned int maxLine(matrixElement *matrix, int inf_l, int sup_l){
  unsigned int maxLine = matrix[0].line;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].line > maxLine)
      maxLine = matrix[i].line;
  return maxLine;
}
unsigned int maxColmn(matrixElement *matrix, int inf_l, int sup_l){
  unsigned int maxColmn = matrix[0].column;
  int i;
  for (i = inf_l; i < sup_l; i++)
    if (matrix[i].column > maxColmn)
      maxColmn = matrix[i].column;
  return maxColmn;
}

void removeZeros(matrixElement *matrix, int inf_l, int sup_l){
  int i, f;
  for (i = inf_l; i <= sup_l; i++){
    if (matrix[i].value == elementZero){
      for (f = i; f < sup_l-1; f++){ /*Replaces element by the next one*/
        matrix[f] = matrix[f+1];
      }
    i--;
    lastElement--;
    }
  }
}

void sort_lines(matrixElement *matrix, unsigned int inf_l, unsigned int sup_l){
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

void sort_columns(matrixElement *matrix, unsigned int inf_l, unsigned int sup_l){
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

double matrix_density(matrixElement *matrix){
  int size = (maxLine(matrix,0,lastElement)- minLine(matrix,0,lastElement)+1) *
  (maxColmn(matrix,0,lastElement)-minColmn(matrix, 0,lastElement)+1); /* Finds out the matrix size */
  double density = (double)lastElement / size;
  return density;
}

/* Compression-specific functions */
double line_density(matrixElement *matrix, unsigned int line){
  int line_elements = (maxColmn(matrix,0,lastElement)-minColmn(matrix,0,lastElement)+1);
  int nonZeroElements = 0, i;
  for (i = 0; i < lastElement; i++)
    if (matrix[i].line == line)
      nonZeroElements++;
  return (nonZeroElements/ (double) line_elements);
}

unsigned int highestDensityLine(matrixElement *matrix, matrixElement *auxiliary, int auxiliarySize){
  unsigned int line,i;
  line = matrix[0].line;
  for (i = 0; i < auxiliarySize; i++){ /* Goes on matrix a checks that line density*/
    if(line_density(matrix,auxiliary[i].line) > line_density(matrix,line))
      line = matrix[i].line;
    else if (line_density(matrix,auxiliary[i].line) == line_density(matrix,line)){
      if (matrix[i].line < line)
        line = matrix[i].line;
    }
  }
  return line;
}

void removeLine(matrixElement *auxiliary, unsigned int line, int auxiliarySize){
  int i, f;
  for (i = 0; i < lastElement; i++)
    if (auxiliary[i].line == line)
      for (f = i; f < lastElement-1; f++) /*Replaces element by the next one*/
        auxiliary[f] = auxiliary[f+1];
  auxiliarySize--;
}
