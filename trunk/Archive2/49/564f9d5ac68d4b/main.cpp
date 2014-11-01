#include <iostream>
#include <array>
#include <vector>
using namespace std;
int main()
{
    std::vector<int> value_initialized ;
    std::cout << "value_initialized: " ;
    for( int i : value_initialized ) std::cout << i << ' ' ; 
    std::cout << '\n' ;

    std::vector<int> default_initialized ;
  
    
    double* x1 = new double;
    double* x2 = new double();
    double* x3 = new double{};
    double* x4 = new double[5];
    double* x6 = new double[5] {{{1}},{2},{3},{4},{5}};
    cout<<endl<<*x1<<endl<<*x2<<*x3<<*x4<<*x6;
    

     

}
