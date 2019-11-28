#ifndef StackHeader
#define StackHeader

typedef struct mod{

  char id;
  int cdr[2];
  struct mod *next;

}mod;

void StackInsert(mod **head,char id, int cd0,int cd1);
mod* HeadRemove(mod **head);
void FreeStack(mod *head);
#endif
