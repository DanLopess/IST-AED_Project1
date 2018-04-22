#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(){
  char command;
  char string[50];
  int linha = 0;

  scanf("%c*[^' ']", &command);

  if (command == 'w')
    scanf("%s", string);
  else
    scanf("%d", &linha);
  printf("%d %s", linha, string);
  return 0;
}
