#include <cstdio>

void func(int i)
{
    if(i > 0)
    {
        printf("%p\n", &i);
        func(i - 1);
    }
}

int main()
{
  int i = 7;
  printf("%d\n", &i);
  func(i);
}
