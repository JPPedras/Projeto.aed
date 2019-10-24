#include<stdio.h>
#include<stdlib.h>

#include"analysis.h"
#include"files.h"


int check(pb *prob){

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
