#ifndef AnalysisHeader
#define AnalysisHeader

#include"files.h"

int InitCheck(pb *prob,int *season);  //problema A
int check_b(pb *prob);  //problema B
int check_c(pb *prob);  //problema C
void Tree_Tent(pb* prob,int n,int m,int *result);
int SolveMapL(pb *prob);
int PutR(pb *prob, int *lines, int *columns);
int PutT(pb *prob, int *lines, int *columns);


#endif
