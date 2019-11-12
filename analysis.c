#include<stdio.h>
#include<stdlib.h>

#include"analysis.h"
#include"files.h"


int check_a(pb *prob){

  int tent_count[2]={0}, tree_count=0, i,j;

  for(i=0;i<prob->L;i++){
    tent_count[0]+=prob->lines[i];
  }
  for(i=0;i<prob->C;i++){
    tent_count[1]+=prob->columns[i];
  }
  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      if(prob->map[i][j]=='A')
        tree_count++;
    }
  }

  if(tent_count[0]!=tent_count[1] || tree_count<tent_count[0])
    return(0);

  return 1;
}

int check_b(pb *prob){

  int tree_count=0,i,j,k=0,*tent_count,*a_sides,retval=0,op[3]={-1,0,1},tents=0;

  a_sides=(int*)malloc(8*sizeof(int));
  tent_count=(int*)malloc(2*sizeof(int));

  for(i=0;i<8;i++){
    a_sides[i]=0;
  }
  for(i=0;i<2;i++){
    tent_count[i]=0;
  }

  if(prob->cd[0]==0){
    a_sides[0]=-1;
    a_sides[1]=-1;
    a_sides[2]=-1;
  }
  if(prob->cd[0]==(prob->L)-1){
    a_sides[5]=-1;
    a_sides[6]=-1;
    a_sides[7]=-1;
  }
  if(prob->cd[1]==0){
    a_sides[0]=-1;
    a_sides[3]=-1;
    a_sides[5]=-1;
  }
  if(prob->cd[1]==(prob->C)-1){
    a_sides[2]=-1;
    a_sides[4]=-1;
    a_sides[7]=-1;
  }
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(op[i]==0 && op[j]==0)
        continue;
      if(a_sides[k]==0){
        if(prob->map[(prob->cd[0])+op[i]][(prob->cd[1])+op[j]]=='T')
          tents++;
        if((prob->map[(prob->cd[0])+op[i]][(prob->cd[1])+op[j]]=='A') && (op[i]==0 || op[j]==0))
          tree_count++;
      }
      k++;
    }
  }
  if(tree_count==0 || tents!=0){
    retval=1;
  }

  for(i=0;i<prob->C;i++){
    if((prob->map[prob->cd[0]][i]=='T') && prob->cd[1]!=i)
      tent_count[0]++;
  }
  for(i=0;i<prob->L;i++){
    if((prob->map[i][prob->cd[1]]=='T') && prob->cd[0]!=i)
      tent_count[1]++;
  }

  if((tent_count[0]==prob->lines[prob->cd[0]]) || (tent_count[1]==prob->columns[prob->cd[1]])){
    retval=1;
  }

  free(a_sides);
  free(tent_count);

  //printf("trees:%d\n",tree_count);
  //printf("tents:%d\n",tents);
  return(retval);
}


int check_c(pb *prob){

  int result=0,i,j,k;

  /*result=check_a(prob);

  if(result==0){
    return(1);
  }*/
  prob->flag=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->flag[i]=(char*)malloc(prob->C*sizeof(char));
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->flag[i][j]='0';
    }
  }


  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->cd[0]=i;
      prob->cd[1]=j;
      if(prob->map[i][j]=='T'){
        result=check_b(prob);
        if(result==1){
          for(i=0;i<prob->L;i++){
            free(prob->flag[i]);
          }
          free(prob->flag);
          return(1);
        }
      }
    }
  }


  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      if(prob->map[i][j]=='T'){
        result=Tree_Tent(prob,i,j);
        if(result==1){
          for(k=0;k<prob->L;k++){
            free(prob->flag[k]);
          }
          free(prob->flag);
          return(1);
        }
      }
    }
  }


  for(i=0;i<prob->L;i++){
    free(prob->flag[i]);
  }
  free(prob->flag);

  return(0);
}

int Tree_Tent(pb *prob,int n,int m){

  int result,op[3]={-1,0,1},i,j;
  char S;
  if(prob->flag[n][m]=='1'){
    printf("oi\n");
    return(0);
  }

  if(prob->map[n][m]=='T')
    prob->flag[n][m]='1';

  if(prob->map[n][m]=='A')
    S='T';
  else
    S='A';

  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(op[i]==op[j] || op[i]==-op[j])
        continue;
      if(n+op[i]>=0 && m+op[j]>=0){
        if(prob->map[n+op[i]][m+op[j]]==S){
          printf("n+op[i]: %d   m+op[j]:%d\n",n+op[i],m+op[j]);
          result=Tree_Tent(prob,n+op[i],m+op[j]);
          if(prob->map[n][m]=='T' && result==1)
            return 1;
          if(prob->map[n][m]=='A' && result==0)
            return 0;
        }
      }
    }
  }

  /*if(prob->map[i][j]=='T'){
    prob->flag[i][j]='1';
    if(i-1>=0)
      if(prob->map[i-1][j]=='A')
        Tree_Tent(prob,i-1,j);
    if(j-1>=0)
      if(prob->map[i][j-1]=='A')
        Tree_Tent(prob,i,j-1);
    if(i+1<prob->C)
      if(prob->map[i+1][j]=='A')
        Tree_Tent(prob,i+1,j);
    if(j+1<prob->L)
      if(prob->map[i][j+1]=='A')
        Tree_Tent(prob,i,j+1);
  }*/

  return 0;
}
