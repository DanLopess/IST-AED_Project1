void compress_matrix(matrixElement *matrix){
  if (matrix_density(matrix) > 0.5)
    printf("dense matrix");
  else{
    int lastPos=0;/*stores the last position of vector and index*/
    unsigned long int linesByDensity[MAXELEMENTS]; /*Stores lines by density*/
    double value[2*MAXELEMENTS];
    unsigned long int index[2*MAXELEMENTS];
    unsigned long int offset[MAXELEMENTS][1], nOffset = 0;

    /*Fill values with elementZero and fill index with 0*/
    for (i = 0; i < 2*MAXELEMENTS; i++){
      values[i] = elementZero;
      index[i] = 0;
    }
    int lines_count = buildAuxiliary(matrix, linesByDensity); /*number of lines*/
    do{
      int f,lineAdded=0;
      for (f = 0; f <= lastPos; f++) /*For each position in value and index*/
        double completeLine[MAXELEMENTS];
        if(testPlaceValues(matrix,value,lastElement,f,completeLine,linesByDensity[line_count])){
          /*add line to value and index*/
          int lineSize=maxColmn(matrix,0,lastElement)-minColmn(matrix,0,lastElement);
          for (int i = 0; i < (f + lineSize); i++)
            if (completeLine[i] != elementZero){
            value[i] = completeLine[i]; /*adds value*/
            index[i] = linesByDensity[lineAdded];/*adds line*/
            }
          if (lastPos < f + lineSize)
            lastPos = f + lineSize;
          offset[linesByDensity[lineAdded]][0] = f;
          nOffset++;
          lineAdded++;
          break;
        }
    } while(lineAdded <= lines_count);
    sort_lines(offset,0,nOffset); /*Fazer funcao especifica para sorts*/
    compressedMatrix(value,index,offset,nValues,nOffset); /*Prints compression*/
  }
}

/*Falta:
- buildAuxiliary
- SORT para offset e densidades

*/


/*FUNCOES AUXILIARESSSSSSSS*/
/* Compression-specific functions */
void sortVector(unsigned long int *vector,l_sup,l_inf){

}
double line_density(matrixElement *matrix, unsigned long int  line){
  /*
 * Function: matrix_density
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
  int i;
  int linesCount = 0;
  /*Puts all lines on the vector linesByDensity*/
  for (i = 0; i < lastElement; i++){
    int proceed=0;
    for (f = 0; f < linesCount; f++){
      if(matrix[i].line == linesByDensity[f]){
        proceed = 1;
        break;
      }
    }
    if (!proceed){
      linesByDensity[linesCount]=matrix[i].line;
      linesCount++;
    }
  }
  /*Does the sorting*/
  sort_by_density(linesByDensity);
  for (f = 0; f < linesCount; f++){
    if (line_density(linesByDensity,linesByDensity[0]) !=
        line_density(linesByDensity,linesByDensity[f])){
          /*when a different density line is found*/
      sort_lines(linesByDensity,0,f-1); /*Sorts lines with same density by number*/
    }
  }
  return linesCount;
}

int testPlaceValues(matrixElement *matrix, double *value, int lastElement,
                      int position, double *completeLine, unsigned long int line){
  /*
 * Function: placeValues_Indexes
 * --------------------
 *  based on the input given, this function will either TRY to compress the
 *  values and indexes of a line and returns 1 if it is possible or 0 if not
 *  input: matrixElement *matrix, double *value, int position,
 *  unsigned long int line
 *  returns: 1 or 0 (test)
 */
  int lineSize=maxColmn(matrix,0,lastElement)-minColmn(matrix,0,lastElement);

  for (int f; f < lineSize; f++){ /*Builds a vector with the complete Line*/
    int added = 0;
    for (int i = 0; i < lastElement; i++)
      if (matrix[i].line == line){
        completeLine[f] = matrix[i].value;
        added = 1;
        break;
      }
      if (!added)
        completeLine[f] = elementZero;
  }
  for (int f = 0 , i = position; i < (position + lineSize); i++){
    if (value[i] != elementZero && completeLine[f] != elementZero)
      return 0; /*Test failed*/

  return 1; /*Test passed*/
  }
}

void compressedMatrix(double *value, unsigned long int *index, int *offset,
                      int nValues, int nOffset){
  /*
 * Function: compressedMatrix
 * --------------------
 *  prints the final compression vectors
 *  input: double *value, unsigned long int *index, int *offset,
 *         int nValues, int nOffset
 *  returns: none
 */
  printf("value =");
  for (i = 0; i < nValues; i++)
    printf(" %.3f", values[i]);
  printf("index =");
  for (i = 0; i < nIndex; i++)
    printf(" %d", index[i]);
  printf("offset =");
  for (i = 0; i < line_count; i++)
    printf(" %d", offset[i]);
}
