#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main()
{
    std::vector<std::string> words = {
        "Hello  Wrrld", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    
    std::map<int , int> mymap;
    mymap.insert(std::make_pair(1,1));
    mymap.insert(std::make_pair(2,2));
    mymap.insert(std::make_pair(3,3));
    mymap.insert(std::make_pair(4,4));
    
    for(auto it :mymap){
    //    std::cout<<i.first<<" "<<i.second<<std::endl;        
    }    
    
    //mymap.sort();
    
    std::vector<int> v = { 0, 0 };
    int i = 0;
    v[i++] = i++;
    std::cout << v[0] << v[1] << std::endl;


       
}
