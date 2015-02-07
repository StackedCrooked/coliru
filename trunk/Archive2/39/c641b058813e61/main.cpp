#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
int main()
{
    
    
     
  //std::string *publisherPtr;
    std::vector<std::string> *ResultPtr;
    std::vector<std::string> Pub{"file1","file2","file3","file4","file5","file6"};
    std::vector<std::string> Sub{"file1","file2","file6","file4","file5"};
    std::sort(Pub.begin(), Pub.end());
    std::sort(Sub.begin(),Sub.end());
 
    std::vector<std::string> v_intersection;
 
    std::set_intersection(Pub.begin(), Pub.end(),
                          Sub.begin(), Sub.end(),
                          std::back_inserter(v_intersection));
    for(std::string n : v_intersection)
        std::cout << n << ' ';

ResultPtr = &v_intersection;

for(std::string n : *ResultPtr)
std::cout << n << ' ';

}