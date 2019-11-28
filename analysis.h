#ifndef AnalysisHeader
#define AnalysisHeader

#include"files.h"
#include"stack.h"

int InitCheck(pb *prob,int *season);  //problema A
int check_b(pb *prob);  //problema B
int check_c(pb *prob);  //problema C
void Tree_Tent(pb* prob,int n,int m,int *result);
int SolveMapL(pb *prob, FILE **fp1,mod *stack);
int PutR(pb *prob, mod *stack);
int PutT(pb *prob, mod *stack);


#endif
