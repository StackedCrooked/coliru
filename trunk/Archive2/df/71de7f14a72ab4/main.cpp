#include <iostream>
#include <cmath>


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
    std::cout << "i \tpow2 \tlog2 \tstd::log2\n";
    for (int i = 3; i < 10000; i = std::max(double(i + 1), i * 1.1))
    {
        std::cout << i
        << " \t" << nextpow2(i)
        << " \t" << (log2(i) + 1)
        << " \t" << std::log(i) + 1
        << '\n';
    }
}


