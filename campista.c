#include<stdio.h>
#include<stdlib.h>
#include"files.h"
#include"analysis.h"

pb *prob;

int main(int argc, char *argv[]){

  FILE *fp;
  int out=0;

  fp=fopen(argv[1],"r");

  if (fp == (FILE*) NULL) {
    exit(1);
  }

  ProbInit(prob);

  while(1){

    out=LoadProb(&fp,prob);
    if(out==1)
      break;

    check(prob);

    FreeMap(prob);

}
  FreeProb(prob);
  fclose(fp);
  return 0;
}
