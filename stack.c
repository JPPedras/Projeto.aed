#include<stdio.h>
#include<stdlib.h>
#include"stack.h"


void StackInsert(mod **head,char id, int cd0,int cd1){

  if(*head!=NULL){
    mod *new;
    new=(mod*)malloc(sizeof(mod));
    new->next = *head;
    *head=new;
    //printf("id:%c\n",head->next->id);
  }
  else{
    printf("oi\n");
    (*head)=(mod*)malloc(sizeof(mod));
    (*head)->next=NULL;
  }
  (*head)->id = id;
  (*head)->cdr[0]=cd0;
  (*head)->cdr[1]=cd1;



  return;
}

mod* HeadRemove(mod **head){

  mod *aux;

  //printf("id:%c\n",(*head)->next->id);
  aux=(*head)->next;
  free(*head);
  *head=aux;

  return (*head);
}

void FreeStack(mod *head){

  mod *aux;

  while(head!=NULL){
    aux=head->next;
    free(head);
    head=aux;
  }
}
