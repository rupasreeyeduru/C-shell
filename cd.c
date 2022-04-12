#include "headers.h"
#include <errno.h>
void cd(imat matrix, paths path)
{ int x;
  if (matrix.no_of_args == 1)
  {
     x=chdir(path->home);
    strcpy(path->prev, path->curr); // for cd change to home
    getcwd(path->curr, 100);
    
  }
  else if (strcmp(matrix.args[1], "-") == 0)
  {
   x= chdir(path->prev);
    strcpy(path->prev, path->curr); //for cd - change to previous path
    getcwd(path->curr, 100);
    printf("%s\n", path->curr);
    
  }

  else if (strcmp(matrix.args[1], "~") == 0)
  {
    x=chdir(path->home);
    strcpy(path->prev, path->curr); // for cd~ change to home path
    getcwd(path->curr, 100);
   
  }
  else
  {
    char *Path = (char *)malloc(1000 * sizeof(char));
    strcpy(Path, matrix.args[1]);
   
    if (Path[0] == '~')
    {
      
      chdir(path->home); // for ~/path change to homae and then path
     x=  chdir(&Path[2]);
    }
    else
    {
    
     x=chdir(matrix.args[1]);
    }
    strcpy(path->prev, path->curr); // for path change to path
    getcwd(path->curr, 100);
  }

  if(x<0)
  perror("error");
}