#include <iostream>

template <size_t X, size_t Y>
void fun (int (&)[X][Y])
{
    std::cout << " do something fun " << std::endl;
}

int main ()
{
  const size_t row (10);
  const size_t col (20);

  int data1[10][20];
  fun ( data1 );// compiles

  int data2[row][col];
  fun ( data2 );// compiles too!

  return 0;
}
