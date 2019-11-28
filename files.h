#ifndef FilesHeader
#define FilesHeader

typedef struct pb{

  int L;
  int C;
  int cd[2];
  int *lines;
  int *columns;
  char **map;
  int *Lslots;
  int *Cslots;
  //char **trees;
  //char **flag;

}pb;



int LoadProb(FILE **fp,pb *prob);

void FreeProb(pb *prob);

void FreeMap(pb *prob);

void ProbInit(pb **prob);

void ExtFile(char *argv, char **fileOut);

void writeFile(pb *prob,int write_val,FILE **fp1);



#endif
