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

  int tree_count=0,i,*tent_count,*a_sides,retval=0;

  a_sides=(int*)malloc(4*sizeof(int));
  tent_count=(int*)malloc(2*sizeof(int));

  for(i=0;i<4;i++){
    a_sides[i]=0;
  }
  for(i=0;i<2;i++){
    tent_count[i]=0;
  }

  if(prob->cd[0]==0)
    a_sides[0]=-1;
  if(prob->cd[0]==(prob->L)-1)
    a_sides[1]=-1;
  if(prob->cd[1]==0)
    a_sides[2]=-1;
  if(prob->cd[1]==(prob->C)-1)
    a_sides[3]=-1;

  if(a_sides[0]==0)
    if(prob->map[(prob->cd[0])-1][(prob->cd[1])]=='A')
      tree_count++;
  if(a_sides[1]==0)
    if(prob->map[(prob->cd[0])+1][(prob->cd[1])]=='A')
      tree_count++;
  if(a_sides[2]==0)
    if(prob->map[(prob->cd[0])][(prob->cd[1])-1]=='A')
      tree_count++;
  if(a_sides[3]==0)
    if(prob->map[(prob->cd[0])-1][(prob->cd[1]+1)]=='A')
      tree_count++;

  if(tree_count==0){
    retval=1;
  }

  for(i=0;i<prob->C;i++){
    if(prob->map[prob->cd[0]][i]=='T')
      tent_count[0]++;
  }
  for(i=0;i<prob->L;i++){
    if(prob->map[i][prob->cd[1]]=='T')
      tent_count[1]++;
  }
  if((tent_count[0]==prob->lines[prob->cd[0]]) || (tent_count[1]==prob->columns[prob->cd[1]])){
    retval=1;
  }

  free(a_sides);
  free(tent_count);

  printf("trees:%d\n",tree_count);
  return(retval);
}


int check_c(pb *prob){



  return(1);
}
