#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void calc_primes(size_t limit) 
{
    std::vector<bool> bv;
    bv.reserve(limit);

    double sqrt = std::sqrt(limit);
    
    for (size_t x = 1; x <= sqrt; x++)
    {
      for (size_t y = 1; y <= sqrt; y++)
      {
        size_t x2 = x*x;
        size_t y2 = y*y;
        size_t n = 4*x2 + y2;
        if (n <= limit && (n%12 == 1 || n%12 == 5))
          bv[n] ^= true;
    
        n -= x2;
        if (n <= limit && n%12 == 7)
          bv[n] ^= true;
    
        n -= 2 * y2;
        if (x > y && n <= limit && n%12 == 11)
          bv[n] ^= true;
      }
    }
    
    for (size_t n = 5; n <= sqrt; n += 2)
      if (bv[n])
      {
        size_t s = n*n;
        for (size_t k = s; k <= limit; k += s)
          bv[k] = false;
      }
    bv[2] = true;
    bv[3] = true;
    
    for(size_t i = 0; i < bv.size(); ++i)
    {
        if(bv[i]) std::cout << i << " ";
    }
}

int main()
{
    calc_primes(10);
}
