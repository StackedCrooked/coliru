#include <stdio.h>
#include <vector>
using namespace std;

struct Test
{
    std::vector<int> *num;
    int *n;
};

int main()
{
    Test *t = new Test();
    t->num = new std::vector<int>;
    t->num->assign(10, 10);
    t->n = new int[20];
    int *testN = t->n;
    std::vector<int> *testV;
    
    testV = t->num;
    delete t;
    
//I can print n's memory
  printf("%d\n", testN[0]);

//I can't print num's memory; its size is 0.
  printf("%d\n", testV->size() );
}