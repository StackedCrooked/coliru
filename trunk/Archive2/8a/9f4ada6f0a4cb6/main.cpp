#include <cstring>
#include <algorithm>
#include <time.h>
#include <cstdio>

using namespace std;

static const char alphanum[] =
"abcdefghijklmnopqrstuvwxyz";

const int stringLength = sizeof(alphanum) - 1;
const int size = 10;

char* genRandom()
{
  char str[10];

    for(int i=0; i<10;++i)
    str[i]=alphanum[rand() % stringLength];
    

    return str;
}

struct TZap{
                char Name[30];
                char Stamp[30];
                char Date[30];
                bool Repair;
     } ;

int cmp(const void *lvalue, const void *rvalue){
  return strcmp(((TZap*)lvalue)->Name,((TZap*)rvalue)->Name);//==1?true:false;
}

int main()
{
  srand(time(NULL));

  TZap *array = new TZap[size];
  char date[] = "1.1.2014";

  for(int i=0;i<size;++i){
      strcpy(array[i].Date,date);
      strcpy(array[i].Name,genRandom());
      strcpy(array[i].Stamp,genRandom());
      array[i].Repair=i/2;
    }

  std::qsort(array,size,sizeof(TZap),cmp);

  for(int i=0; i< size;++i)
      puts(array[i].Name);

    return 0;
}