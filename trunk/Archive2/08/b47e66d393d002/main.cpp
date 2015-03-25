#include<iostream>
#include<vector>
#include<algorithm>
#include<string>


int main()
{
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(1);
    vec.push_back(8);
    
    std::vector<int>::iterator itr;
    
    std::sort(vec.begin(),vec.end());
        
    for(itr = vec.begin();itr!=vec.end();++itr)
        std::cout << *itr << std::endl;      
    
        
}
