#include <vector>
#include <iostream>

 int main()
 {
    std::vector<int> v;
    v.push_back(42);
    int* p = &v[0];
    if (p)
      std::cout<<"Result:"<<*p;
      
    const std::vector<int> cv (v);
    
    
    //int* const p2 = &cv[0];
    int* const p2 = new int (5);
    *p2 = 7;
    if (p2)
      std::cout<<"Result:"<<*p;
    
          
 };