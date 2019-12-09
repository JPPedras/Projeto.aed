#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"files.h"
#include"analysis.h"
#include"stack.h"

pb *prob;     //guarda a informacao relativa ao problema a resolver
mod *stack;   //pilha utilizada para fazer o backtrack quando se chega a um beco sem saida

int main(int argc, char *argv[]){

  FILE *fp,*fp1;
  int out=0, write_val;
  char* fileOut;  //nome do ficheiro de saida

  fp=fopen(argv[1],"r");
  if (fp == (FILE*) NULL) {
    exit(1);
  }
  ExtFile(argv[1],&fileOut);  //cria o nome do ficheiro de saida

  fp1=fopen(fileOut,"w");

  ProbInit(&prob);      //inicializa a estrutura utilizada para guardar o problema

  while(1){

    out=LoadProb(&fp,prob);     //le o ficheiro de entrada e aloca espaco para os diferentes elementos que definem o problema

    if(out==1){
      break;
    }
    else{
      if(InitCheck(prob)==0){   //verifica se o problema esta bem definido
        write_val=-1;
      }
      else{
        write_val=SolveMapL(prob,&fp1,&stack);  //resolve o problema
      }
      if(write_val==-1){
        writeFile(prob,write_val,&fp1);     //caso se tenha concluido que o problema nao tem solucao escreve essa informacao no ficheiro de saida
      }
      FreeMap(prob);      //liberta a memoria relativa aos elementos que definem o problema
    }
}
  FreeProb(prob);     //liberta a estrutura do prolema
  FreeStack(stack);   //liberta a pilha
  free(fileOut);

  fclose(fp);
  fclose(fp1);

  return 0;
}
