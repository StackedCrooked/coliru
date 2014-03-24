#include <stdio.h>
#include <math.h>

inline float safediv(float a, float b) { return b == 0.0f ? b : a/b; }

//#define VERY_SMALL_NUMBER (4e-19f)  // ~ sqrt(FLT_MIN)
//inline float safediv(float a, float b) { return b > VERY_SMALL_NUMBER ? a/b : (b < -VERY_SMALL_NUMBER ? a/b : 0.f); }

int main()
{
  float x = 1.0;
  float y = -1e-34;
  for (int i = 0; i < 10; i++)
  {
    float r = safediv(x, y);    
    printf("%e / %e = %e\n", x, y, r);
    y *= -0.22f;
  }
  return 0;
}