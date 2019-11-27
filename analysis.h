#ifndef AnalysisHeader
#define AnalysisHeader

#include"files.h"

int InitCheck(pb *prob,int *season);  //problema A
int check_b(pb *prob);  //problema B
int check_c(pb *prob);  //problema C
void Tree_Tent(pb* prob,int n,int m,int *result);
int SolveMapL(pb *prob, FILE **fp1);
int PutR(pb *prob);
int PutT(pb *prob);


#endif
