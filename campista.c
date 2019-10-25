#include<stdio.h>
#include<stdlib.h>

#include"files.h"
#include"analysis.h"

pb *prob;

int main(int argc, char *argv[]){

  FILE *fp;
  int out=0, write_val;

  fp=fopen(argv[1],"r");

  if (fp == (FILE*) NULL) {
    exit(1);
  }

  ProbInit(&prob);

  while(1){

    out=LoadProb(&fp,prob);
    if(out==1)
      break;

    switch(prob->type){
      case 'A':
        write_val=check_a(prob);
        break;
      case 'B':
        write_val=check_b(prob);
        break;
      default:
        write_val=check_c(prob);
    }

    printf("write_val: %d\n",write_val);

    FreeMap(prob);

}
  FreeProb(prob);
  fclose(fp);
  return 0;
}
