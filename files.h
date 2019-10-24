#ifndef FilesHeader
#define FilesHeader


typedef struct pb{

  int L;
  int C;
  char type;
  int cd[2];
  int *lines;
  int *columns;
  char **map;

}pb;


/*


*/
int LoadProb(FILE **fp,pb *prob);

void FreeProb(pb *prob);

void FreeMap(pb *prob);

void ProbInit(pb *prob);



#endif
