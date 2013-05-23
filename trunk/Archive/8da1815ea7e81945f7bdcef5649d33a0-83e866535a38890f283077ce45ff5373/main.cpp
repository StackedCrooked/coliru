#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct node {
  int num;
  node *next;
};

int main()
{

for (int i=11; i<=15; i++) {
  node *new_etc;
  new_etc = (node*) malloc(sizeof(node));
  cout << new_etc << endl;
}

}
