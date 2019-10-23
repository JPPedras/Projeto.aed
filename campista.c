#include<stdio.h>
#include<stdlib.h>

#include"print.h"

typedef struct{

  int L;
  int C;
  int *lines;
  int *columns;
  char **map;

}pb;

int main(int argc, char *argv[]){

  FILE *fp;
  pb *prob;

  prob=(pb*)malloc(sizeof(pb));

  fp=fopen(argv[1],"r");

  do{
    

  }while(feof(fp)!=NULL);


  free(prob);


  return 0;
}
