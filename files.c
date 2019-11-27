#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"files.h"

int LoadProb(FILE **fp, pb *prob){

  int i;

  if(fscanf(*fp,"%d %d",&(prob->L),&(prob->C))<2){
    return 1;
  }

  prob->cd[0]=0;
  prob->cd[1]=0;


  prob->lines=(int*)malloc(prob->L*sizeof(int));
  if(prob->lines==NULL){
    exit(0);
  }

  prob->columns=(int*)malloc(prob->C*sizeof(int));
  if(prob->columns==NULL){
    exit(0);
  }

  prob->Lslots=(int*)malloc(prob->L*sizeof(int));
  if(prob->Lslots==NULL){
    exit(0);
  }

  prob->Cslots=(int*)malloc(prob->C*sizeof(int));
  if(prob->Cslots==NULL){
    exit(0);
  }

  for(i=0;i<prob->L;i++){
    prob->Lslots[i]=0;
  }
  for(i=0;i<prob->C;i++){
    prob->Cslots[i]=0;
  }

  prob->map=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->map[i]=(char*)malloc(((prob->C)+1)*sizeof(char));
  }

  /*prob->trees=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->trees[i]=(char*)malloc(prob->C*sizeof(char));
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->trees[i][j]='0';
    }
  }*/


  for(i=0;i<prob->L;i++){
    if(fscanf(*fp,"%d",&(prob->lines[i]))<1)
      return 1;
  }
  for(i=0;i<prob->C;i++){
    if(fscanf(*fp,"%d",&(prob->columns[i]))<1)
      return 1;
  }

  //printf("ok\n");

  for(i=0;i<prob->L;i++){
    //for(j=0;j<prob->C;j++){
    if(fscanf(*fp,"%s",prob->map[i])<1)
      return 1;
    //}
  }

  /*for(i=0;i<prob->L;i++){
    printf("%d",prob->lines[i]);
  }
  printf("i\n");
  for(i=0;i<prob->C;i++){
    printf("%d",prob->columns[i]);
  }
  printf("\n\n\n");*/

  /*for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      printf("%c",prob->map[i][j]);
    }
    printf("\n");
  }*/
  //printf("L:%d C:%d type:%c\n",prob->L,prob->C,prob->type);


  return(0);
}




void FreeProb(pb *prob){
  free(prob);
}

void FreeMap(pb *prob){
  int i;

  free(prob->lines);
  free(prob->columns);
  free(prob->Lslots);
  free(prob->Cslots);
  for(i=0;i<prob->L;i++){
    free(prob->map[i]);
  }
  free(prob->map);

}

void ProbInit(pb **prob){

  (*prob)=(pb*)malloc(sizeof(pb));
  //if((*prob)==NULL)
  //printf("erro de memoria\n");
}

void ExtFile(char* argv, char** fileOut){

  int i=0;

  (*fileOut)=(char*)malloc((strlen(argv)+2)*sizeof(char));

  while(argv[i]!='.'){
    (*fileOut)[i]=argv[i];
    i++;
  }
  (*fileOut)[i]='\0';
  strcat(*fileOut,".tents");

  return;
}

void writeFile(pb *prob,int write_val,FILE **fp1){

  int i,j;

  fprintf(*fp1,"%d %d %d\n",prob->L,prob->C,write_val);
  if(write_val==1){
    for(i=0;i<prob->L;i++){
      for(j=0;j<prob->C;j++){
        if(prob->map[i][j]=='R'){
          fprintf(*fp1,".");
        }
        else{
          fprintf(*fp1,"%c",prob->map[i][j]);
        }
      }
      fprintf(*fp1,"\n");
    }
  }
  fprintf(*fp1,"\n");


}
