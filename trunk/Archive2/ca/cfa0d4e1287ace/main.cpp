#include <iostream>
#include <random>
int roundnew(double d)
{
  return floor(d + 0.5);
}
int main()
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(10,1);

    for (int n = 0; n < 12; ++n) {
       printf("%d\n",roundnew(distribution(generator)));
    }

return 0;
}