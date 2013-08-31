#include <iostream>
#include <string>
#include <vector>

using namespace std;

void scale(std::vector<double>& v, const double& x)
{
      for (auto p = v.begin(); p != v.end(); ++p)
           *p /= x;
}

int main()
{
    std::vector<double> v = {11, 22, 33, 44, 55};    
    
    scale(v, v[0]);
    
    cout << 
}
