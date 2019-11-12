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

    if(prob->cd[0]>=prob->L || prob->cd[1]>=prob->C){
      write_val=-1;
    }
    else{
      switch(prob->type){
        case 'A':
          write_val=check_a(prob);
          break;
        case 'B':
          write_val=check_b(prob);
          break;
        case 'C':
          write_val=check_c(prob);
          break;
        default:
          write_val=-1;
      }
    }

    printf("write_val: %d\n",write_val);

    FreeMap(prob);

}
  FreeProb(prob);
  fclose(fp);
  return 0;
}
