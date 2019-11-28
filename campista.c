#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"files.h"
#include"analysis.h"
#include"stack.h"

pb *prob;

int main(int argc, char *argv[]){

  FILE *fp,*fp1;
  int out=0, write_val,season=0;
  char* fileOut;
  mod *stack;
  //char **tempmap;

  fp=fopen(argv[1],"r");
  if (fp == (FILE*) NULL) {
    exit(1);
  }
  ExtFile(argv[1],&fileOut);

  fp1=fopen(fileOut,"w");

  ProbInit(&prob);
  stack=StackInit();

  while(1){

    //char **tempmap;

    out=LoadProb(&fp,prob);

    if(out==1){
      break;
    }
    else{


      //season=0 : tents<trees (baixa) | season=1 : tents=trees (alta)
      if(InitCheck(prob,&season)==0){
        write_val=-1;
      }
      else{
        write_val=SolveMapL(prob,&fp1,stack);
      }
      if(write_val==-1){
        writeFile(prob,write_val,&fp1);
      }
      FreeMap(prob);
    }
}
  FreeProb(prob);
  FreeStack(stack);
  free(fileOut);

  fclose(fp);
  fclose(fp1);

  return 0;
}
