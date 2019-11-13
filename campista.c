#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"files.h"
#include"analysis.h"

pb *prob;

int main(int argc, char *argv[]){

  FILE *fp,*fp1;
  int out=0, write_val;
  char* fileOut;
  int i=0;

  fp=fopen(argv[1],"r");
  if (fp == (FILE*) NULL) {
    exit(1);
  }
  ExtFile(argv[1],&fileOut);

  fp1=fopen(fileOut,"w");

  ProbInit(&prob);

  while(1){


    out=LoadProb(&fp,prob);

    if(out==1){

      break;
    }
    else if(out==2){
      write_val=-1;
      writeFile(prob,write_val,&fp1);
    }
    else{
      switch(prob->type){
        case 'A':
          write_val=check_a(prob);
          break;
        case 'B':
          //printf("%d\n",i);
          write_val=check_b(prob);
          break;
        case 'C':
          write_val=check_c(prob);
          break;
        default:
          write_val=-1;
      }
      writeFile(prob,write_val,&fp1);

      FreeMap(prob);
    }
    i++;
}
  FreeProb(prob);
  free(fileOut);

  fclose(fp);
  fclose(fp1);

  return 0;
}
