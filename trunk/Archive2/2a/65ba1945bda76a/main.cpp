#include <iostream>


inline int nextpow2(int x)
{
    if (x < 0)
    {
        return 0;
    }
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}


inline int log2(int x)
{
  int y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}



int main()
{
    std::cout << "i pow2 log2\n";
    for (int i = 2; i < 100000; i = 3 * i / 2)
    {
        std::cout << i
        << ' ' << nextpow2(i)
        << ' ' << (log2(i) + 1)
        << '\n';
    }
}














