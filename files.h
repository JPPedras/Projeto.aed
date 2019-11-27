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

typedef struct mod{

  char id;
  int cdr[2];
  mod next;
}mod;


int LoadProb(FILE **fp,pb *prob);

void FreeProb(pb *prob);

void FreeMap(pb *prob);

void ProbInit(pb **prob);

void ExtFile(char *argv, char **fileOut);

void writeFile(pb *prob,int write_val,FILE **fp1);



#endif
