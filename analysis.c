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

  if(tent_count[0]!=tent_count[1] || tree_count<tent_count[0] || tree_count<tent_count[1])
    return(0);

  return 1;
}

int check_b(pb *prob){

  int tree_count=0,i,j=1,*diret;

  diret=(int*)malloc(4*sizeof(int));

  if(prob->cd[0]==0)
    diret[0]=-1;
  if(prob->cd[0]==(prob->L)-1)
    down=-1


  for(i=0;i<2;i++){

    if((prob->map[(prob->cd[0])+i][(prob->cd[1])-j]=='A') || (prob->map[(prob->cd[0])-j][(prob->cd[1])+i]=='A')) {
        tree_count++;
    }
    j=0;
  }

  printf("trees:%d\n",tree_count);
  return(1);
}


int check_c(pb *prob){



  return(1);
}
