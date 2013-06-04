#include <vector>
#include <stdio.h>

typedef struct vectag
  {
    std::vector<float> *X;
  } vec;

int main ()
  {
    vec A;
    A.X = new std::vector<float>(0);

    A.X->push_back(5.0);

    // This next line is the problem:
    float C = (*A.X)[0];

    printf("%f\n", C);
    return 1;
  }