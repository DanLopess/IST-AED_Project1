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
  matrixElement aux_vector[MAXELEMENTS];
  int minColmn
}

void removesZeros(matrixElement *matrix, l_inf,l_sup){
  
}

/*Fazer funcao removeZero*/
/*Questionar:
- Como ler a matriz completa : com os args no inicio da main, esta nos slides
- Vetor contem max 10000elementos != 0, linhas e colunas podem ser mt grandes
- tem que remover os zeros
- ver strcopy do nome do ficheiro lido

*/
