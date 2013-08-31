#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;

double getSum(const double a[], int size, double& threshold);


int main()
{
double a[5]={10.0,11.0,9.9,12.0, 13.6};

double sum;

sum=getSum(a, 5, 10.0);
}
