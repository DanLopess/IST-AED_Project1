/********************************************************
Library designed by Daniel Lopes

This library has been created in order to simplify
the main code by 'hiding' the small auxiliary functions
while leaving the big functions for the main code

Code Subject: Sparse Matrices
**********************************************************/
int minLine(matrixElement *matrix, int l_inf, int l_sup){
  int minLine = matrix[0].line, i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].line < minLine)
      minLine = matrix[i].line;
  return minLine;
}
int minColmn(matrixElement *matrix, int l_inf, int l_sup){
  int minColmn = matrix[0].column, i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].column < minColmn)
      minColmn = matrix[i].column;
  return minColmn;
}
int maxLine(matrixElement *matrix, int l_inf, int l_sup){
  int maxLine = matrix[0].line, i;
  for (i = l_inf; i < lastElement; i++)
    if (matrix[i].line > maxLine)
      maxLine = matrix[i].line;
  return maxLine;
}
int maxColmn(matrixElement *matrix, int l_inf, int l_sup){
  int maxColmn = matrix[0].column, i;
  for (i = l_inf; i < l_sup; i++)
    if (matrix[i].column > maxColmn)
      maxColmn = matrix[i].column;
  return maxColmn;
}
