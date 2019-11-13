#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"files.h"

int LoadProb(FILE **fp, pb *prob){

  int i,j;

  if(fscanf(*fp,"%d %d %c",&(prob->L),&(prob->C),&(prob->type))<3){
    return 1;
  }


  if(prob->type=='B'){
    if(fscanf(*fp,"%d %d",&(prob->cd[0]),&(prob->cd[1]))<2){
      return 1;
    }
    if(prob->cd[0] >= prob->L || prob->cd[0] < 0 || prob->cd[1] >= prob->C || prob->cd[1] < 0){
      return 1;
    }
  }
  else{
    prob->cd[0]=0;
    prob->cd[1]=0;
  }

  prob->lines=(int*)malloc(prob->L*sizeof(int));
  if(prob->lines==NULL){
    exit(0);
  }

  prob->columns=(int*)malloc(prob->C*sizeof(int));
  if(prob->columns==NULL){
    exit(0);
  }

  prob->map=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->map[i]=(char*)malloc(prob->C*sizeof(char));
  }

  for(i=0;i<prob->L;i++){
    if(fscanf(*fp,"%d",&(prob->lines[i]))<1)
      return 1;
  }
  for(i=0;i<prob->C;i++){
    if(fscanf(*fp,"%d",&(prob->columns[i]))<1)
      return 1;
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      if(fscanf(*fp," %c",&(prob->map[i][j]))<1)
        return 1;
    }
  }

  /*for(i=0;i<prob->L;i++){
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
  printf("L:%d C:%d type:%c\n",prob->L,prob->C,prob->type);*/


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
    printf("erro de memoria\n");
}

void ExtFile(char* argv, char** fileOut){

  int i=0;

  (*fileOut)=(char*)malloc((strlen(argv)+2)*sizeof(char));

  while(argv[i]!='.'){
    (*fileOut)[i]=argv[i];
    i++;
  }
  (*fileOut)[i]='\0';
  strcat(*fileOut,".tents0");

  return;
}

void writeFile(pb *prob,int write_val,FILE **fp1){

  if(prob->type=='B'){
    fprintf(*fp1,"%d %d %c %d %d %d\n\n",prob->L,prob->C,prob->type,prob->cd[0],prob->cd[1],write_val);
  }
  else{
    fprintf(*fp1,"%d %d %c %d\n\n",prob->L,prob->C,prob->type,write_val);
  }

}
