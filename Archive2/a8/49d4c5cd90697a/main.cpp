#include <cstdio>

int main() 
{
    for (int i = -20; i < 20; ++i) {
      double d = i;
      d += 0.5;
      std::printf("%.0f\n", d);
    }
}
