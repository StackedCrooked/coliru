#include <stack>

struct node
{
    int bot,el;
    char name[16];
};

int main()
{
  std::stack < node > S;
  node&b = S.top;
  return 0;
}