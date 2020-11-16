#include<malloc.h>
#include<ctype.h>
  typedef struct user{
  int id;
  char name[8];
  char htel[12];
  char tel[12];
} *usernode;
usernode input();
int save(FILE* fp);
void output(usernode x);
int myWrite(FILE* fp);
int randdat(usernode x);
int cmp1(const void* p1, const void* p2);
int cmp2(const void* p1, const void* p2);
void mysort(usernode pu, int n, int flag);
void usersort(FILE* fp);
int checkid(int xid, FILE* fptr);
