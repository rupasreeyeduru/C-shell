#include "headers.h"

void echo(imat matrix)
{ 
  int N = matrix.no_of_args;
  
  for (int i = 1; i < N - 1; i++)
    printf("%s ", matrix.args[i]);
  printf("%s\n", matrix.args[N - 1]); 
}