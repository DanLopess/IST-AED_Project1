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

void printLines_aux(matrixElement *matrix, int l_inf, int l_sup, unsigned int line, double elementZero){
  int i, f, found_value;
  for (f = 0; f < l_sup; f++) { /* Columns */
    found_value = 0;
    for (i = l_inf; i < l_sup; i++){
      if (matrix[i].line == line && matrix[i].column == (unsigned int) f){
          printf("%.3f ", matrix[i].value);
          found_value = 1;
          break;
      }
      if (!found_value)
        printf("%.3f ", elementZero);
    }
  }
}

void printColumns_aux(matrixElement *matrix, int l_inf, int l_sup, unsigned int column, double elementZero){
  int i, f, found_value;
  for (f = 0; f < maxColmn(matrix,l_inf,l_sup); f++) { /* Lines */
    found_value = 0;
    for (i = l_inf; i < l_sup; i++){
      if (matrix[i].column == column && matrix[i].line == (unsigned int) f){
          printf("%.3f ", matrix[i].value);
          found_value = 1;
          break;
      }
      if (!found_value)
        printf("%.3f ", elementZero);
    }
  }
}
