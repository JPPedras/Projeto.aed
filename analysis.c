#include<stdio.h>
#include<stdlib.h>

#include"analysis.h"
#include"files.h"
#include"stack.h"

int SolveMapL(pb *prob, FILE **fp1, mod **stack){

  //printf("oi\n");

  int i,j,k,l,out=0,act=0,retval=0;



  while(1){
    for(i=0;i<prob->L;i++){
      prob->Lslots[i]=0;
    }
    for(i=0;i<prob->C;i++){
      prob->Cslots[i]=0;
    }
    act=0;
    act=PutR(prob,stack);
    printf("slots[1]:%d\n",prob->Cslots[1]);
    act=PutT(prob,stack);
    //printf("id11:%c\n",stack->id);
    for(k=0;k<prob->L;k++){
      for(l=0;l<prob->C;l++){
        printf("%c",prob->map[k][l]);
      }
      printf("\n");
    }
    printf("\n\n");
    if(act==0){
      break;
    }
    if(act==-1){
      return(-1);
    }
  }

  //printf("oi\n");
  for(i=0;i<prob->L;i++){
    if(prob->lines[i]==0){
      out++;
    }
  }
  for(i=0;i<prob->C;i++){
    if(prob->columns[i]==0){
      out++;
    }
  }
  if(out == prob->L + prob->C){

    writeFile(prob,1,fp1);

    return 1;
  }



  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      if(prob->map[i][j]=='.'){
        act=1;
        prob->lines[i]--;
        prob->columns[j]--;
        prob->Lslots[i]--;
        prob->Cslots[j]--;
        prob->map[i][j]='T';
        printf("Ta-i:%d  j:%d\n",i,j);
        StackInsert(stack,'2',i,j);
        retval=SolveMapL(prob,fp1,stack);
        //printf("id:%c\n",(*stack)->id);
        while((*stack)->id!='2'){
          prob->Lslots[(*stack)->cdr[0]]++;
          prob->Cslots[(*stack)->cdr[1]]++;
          //printf("oi1111");
          if((*stack)->id=='1'){
            prob->lines[(*stack)->cdr[0]]++;
            prob->columns[(*stack)->cdr[1]]++;
          }
          prob->map[(*stack)->cdr[0]][(*stack)->cdr[1]]='.';
          *stack=HeadRemove(stack);
          //printf("passou\n");
        }
        if(retval==1){
          return 1;
        }
        (*stack)->id = '0';
        prob->map[i][j]='R';
        prob->lines[i]++;
        prob->columns[j]++;
      }
    }
  }
  return retval;



    /*árvore binária em que cada vértice é uma árvore e tem:
      -o número de espaços disponiveis à volta;
      -um vetor [up,lf,rh,dn] que indica as posições desses espaços(1:disponivel, 0:indisponivel, -1:fora do mapa)

      1º criar a árvore
      2º ordena-la tipo um acervo


      */

}

int PutR(pb *prob,mod **stack){

  int retval=0,i,j,result=0;

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->cd[0]=i;
      prob->cd[1]=j;
      if(prob->map[i][j]=='.'){
        result=check_b(prob);
        if(result==1){
          prob->map[i][j]='R';
          StackInsert(stack,'0',i,j);
          //printf("id:%c\n",stack->id);
          retval=1;
        }
      }
      if(prob->map[i][j]=='.'){
          //printf("slot:[%d,%d]\n",i,j);
          prob->Lslots[i]++;
          prob->Cslots[j]++;
      }
    }
  }

  return retval;
}
int PutT(pb *prob,mod **stack){

  int retval=0,i,j;
  printf("slots[1]T:%d\n",prob->Cslots[1]);


  for(i=0;i<prob->L;i++){
      if(prob->Lslots[i]==prob->lines[i]){
        for(j=0;j<prob->C;j++){
          if(prob->map[i][j]=='.'){
            retval=1;
            printf("slots:%d -- lines:%d\n",prob->Lslots[i],prob->lines[i]);
            prob->map[i][j]='T';
            StackInsert(stack,'1',i,j);
            printf("Tl-i:%d  j:%d\n",i,j);
            prob->lines[i]--;
            prob->columns[j]--;
            prob->Lslots[i]--;
            prob->Cslots[j]--;
            return retval;
        }
      }
    }
    else if(prob->Lslots[i]<prob->lines[i]){
      //printf("oi11\n");
      return -1;
    }
  }
  //printf("slots[1]L:%d\n",prob->Cslots[1]);

  for(j=0;j<prob->C;j++){
      //printf("slots[%d]L:%d\n",i,prob->Cslots[i]);
      if(prob->Cslots[i]==prob->columns[i]){
        for(i=0;i<prob->L;i++){
          if(prob->map[i][j]=='.'){
            retval=1;
            printf("slots:%d -- columns:%d\n",prob->Cslots[i],prob->columns[i]);
            prob->map[i][j]='T';
            StackInsert(stack,'1',i,j);
            printf("Tl-i:%d  j:%d\n",i,j);
            prob->lines[i]--;
            prob->columns[j]--;
            prob->Lslots[i]--;
            prob->Cslots[j]--;
            return retval;
          }
        }
      }
      else if(prob->Cslots[i]<prob->columns[i]){
        return -1;
      }
  }
  return retval;
}



int InitCheck(pb *prob, int *season){

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
  if(tent_count[0]!=tent_count[1] || tree_count<tent_count[0]){
    return(0);
  }

  if(tree_count==tent_count[0]){
    *season=1;
  }

  return 1;
}

int check_b(pb *prob){

  int tree_count=0,i,j,k=0,retval=0,op[3]={-1,0,1},tents=0;

  if(prob->map[prob->cd[0]][prob->cd[1]]=='A'){
    retval=1;
    return retval;
  }

  for(i=0;i<prob->L;i++){
    if(prob->lines[prob->cd[0]]==0){
      retval=1;
    }
  }
  for(i=0;i<prob->C;i++){
    if(prob->columns[prob->cd[1]]==0){
      retval=1;
    }
  }
  /*result=check_a(prob);
  if(result==0){
    return 1;
  }*/
  //printf("ok2\n");

  //a_sides=(int*)malloc(8*sizeof(int));
  //tent_count=(int*)malloc(2*sizeof(int));

  /*for(i=0;i<8;i++){
    a_sides[i]=0;
  }*/
  /*for(i=0;i<2;i++){
    tent_count[i]=0;
  }*/
  /*
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
  }*/
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(op[i]==0 && op[j]==0)
        continue;
      if((prob->cd[0])+op[i]>=0 && (prob->cd[0])+op[i]<prob->L && (prob->cd[1])+op[j]>=0 && (prob->cd[1])+op[j]<prob->C){
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

  /*if(tree_count==1){
    prob->trees[prob->cd[0]][prob->cd[1]]='1';
  }*/

  /*for(i=0;i<prob->C;i++){
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

  //free(a_sides);
  free(tent_count);*/


  //printf("trees:%d\n",tree_count);
  //printf("tents:%d\n",tents);
  return(retval);
}


int check_c(pb *prob){

  int result=0,i,j;


  /*prob->flag=(char**)malloc(prob->L*sizeof(char*));
  for(i=0;i<prob->L;i++){
    prob->flag[i]=(char*)malloc(prob->C*sizeof(char));
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->flag[i][j]='0';
    }
  }*/


  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      prob->cd[0]=i;
      prob->cd[1]=j;
      if(prob->map[i][j]=='T'){
        result=check_b(prob);
        if(result==1){
          /*for(i=0;i<prob->L;i++){
            free(prob->flag[i]);
          }
          free(prob->flag);*/
          return(1);
        }
      }
    }
  }

  for(i=0;i<prob->L;i++){
    for(j=0;j<prob->C;j++){
      if(prob->map[i][j]=='T'){
        result=0;
        Tree_Tent(prob,i,j,&result);
        if(result==0){
          /*for(k=0;k<prob->L;k++){
            free(prob->flag[k]);
          }
          free(prob->flag);*/
          return(1);
        }
      }
    }
  }


  /*for(i=0;i<prob->L;i++){
    free(prob->flag[i]);
  }
  free(prob->flag);*/
  return(0);
}

void Tree_Tent(pb *prob,int n,int m,int *result){

  int op[3]={1,-1,0},found=0,i=0,j=0;
  char S;

  //printf("flag:%c\n",prob->flag[n][m]);

  /*if(prob->flag[n][m]=='1'){
    return(1);
  }*/
  //prob->map[n][m]=='T'){
  //prob->flag[n][m]='1';
  //}

  if(prob->map[n][m]=='A')
    S='T';
  else
    S='A';

  prob->map[n][m]='.';

  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      //printf("n: %d   m:%d\n",n,m);
      //printf("op[i]: %d   op[j]:%d\n",op[i],op[j]);
      if(op[i]==op[j] || op[i]==-op[j] || n+op[i]<0 || m+op[j]<0 || n+op[i]>(prob->L)-1 || m+op[j]>(prob->C)-1){
        continue;
      }
      if(prob->map[n+op[i]][m+op[j]]==S){
        //printf("n: %d   m:%d\n",n,m);
        //printf("op[i]: %d   op[j]:%d\n",op[i],op[j]);
        //if(prob->flag[n+op[i]][m+op[j]]=='0'){
        found=1;
        Tree_Tent(prob,n+op[i],m+op[j],result);
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

  //printf("found: %d\n",found);
  if(S=='T' && found==0){
    *result=1;
  }
  return;
}
