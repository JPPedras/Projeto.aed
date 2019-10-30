#include<stdio.h>
#include<stdlib.h>

#include"files.h"

int LoadProb(FILE **fp, pb *prob){

  int i,j;

  if(fscanf(*fp,"%d %d %c",&(prob->L),&(prob->C),&(prob->type))<3){
    return 1;
  }


  if(prob->type=='B'){
    fscanf(*fp,"%d %d",&(prob->cd[0]),&(prob->cd[1]));
  }
  else{
    prob->cd[0]=0;
    prob->cd[1]=0;
  }

  prob->lines=(int*)malloc(prob->L*sizeof(int));
  if(prob->lines==NULL){
    printf("Erro de memoria\n");
    exit(0);
  }

  prob->columns=(int*)malloc(prob->C*sizeof(int));
  if(prob->columns==NULL){
    printf("Erro de memoria\n");
    exit(0);
  }

  prob->map=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->map[i]=(char*)malloc(prob->C*sizeof(char));
  }

  for(i=0;i<prob->L;i++){
    fscanf(*fp,"%d",&(prob->lines[i]));
  }
  for(i=0;i<prob->C;i++){
    fscanf(*fp,"%d",&(prob->columns[i]));
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      fscanf(*fp," %c",&(prob->map[i][j]));
    }
  }

  for(i=0;i<prob->L;i++){
    printf("%d",prob->lines[i]);
  }
  printf("\n");
  for(i=0;i<prob->C;i++){
    printf("%d",prob->columns[i]);
  }
  printf("\n");
  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      printf("%c",prob->map[i][j]);
    }
    printf("\n");
  }
  printf("L:%d C:%d type:%c\n",prob->L,prob->C,prob->type);


  return(0);
}


void FreeProb(pb *prob){
  free(prob);
}

void FreeMap(pb *prob){
  int i;

  free(prob->lines);
  free(prob->columns);
  for(i=0;i<prob->L;i++){
    free(prob->map[i]);
  }
  free(prob->map);

}

void ProbInit(pb **prob){

  (*prob)=(pb*)malloc(sizeof(pb));
  if((*prob)==NULL)
    printf("erro\n");
}
