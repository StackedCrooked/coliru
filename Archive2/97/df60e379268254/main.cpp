#include <iostream>
#include <array>
#include <vector>
using namespace std;
int main()
{
    std::vector<int> value_initialized ;
    

    std::vector<int> default_initialized ;
  
    
    double* x1 = new double;
    double* x2 = new double();
    double* x3 = new double{};
    double* x4 = new double[5];
    cout<<endl<<*x1<<endl<<*x2<<*x3<<*x4;
     

}
