/********************************************************
Library designed by Daniel Lopes

This library has been created in order to simplify
the main code by 'hiding' the small auxiliary functions
while leaving the big functions for the main code

Code Subject: Sparse Matrices
**********************************************************/
unsigned int minLine(matrixElement *matrix, int l_inf, int l_sup){
  unsigned int minLine = matrix[0].line;
  int i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].line < minLine)
      minLine = matrix[i].line;
  return minLine;
}
unsigned int minColmn(matrixElement *matrix, int l_inf, int l_sup){
  unsigned int minColmn = matrix[0].column;
  int i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].column < minColmn)
      minColmn = matrix[i].column;
  return minColmn;
}
unsigned int maxLine(matrixElement *matrix, int l_inf, int l_sup){
  unsigned int maxLine = matrix[0].line;
  int i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].line > maxLine)
      maxLine = matrix[i].line;
  return maxLine;
}
unsigned int maxColmn(matrixElement *matrix, int l_inf, int l_sup){
  unsigned int maxColmn = matrix[0].column;
  int i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].column > maxColmn)
      maxColmn = matrix[i].column;
  return maxColmn;
}

double line_density(matrixElement *matrix, int line){
  int line_elements = (maxColmn(matrix,0,lastElement)-minColmn(matrix,0,lastElement)+1);
  int nonZeroElements = 0, i;
  for (i = 0; i < lastElement; i++)
    if (matrix[i].line == line)
      nonZeroElements++;
  return (nonZeroElements/ (double) line_elements);
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

/*Falta:
- Como ler a matriz completa : com os args no inicio da main, esta nos slides
- fazer ordenacao
- fazer compressao

*/
