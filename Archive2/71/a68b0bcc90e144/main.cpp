#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main(){
     std::vector<int> vec={1,2,6,7,8};
     std::vector<std::string> vec2={"7","khat","code"};
     
     //ghabl az c++14 mojaz be estefade az [](auto a,auto b) naboodid 
     auto gLambda=[](auto a,auto b){ return a>b;};
     
     std::sort(vec.begin(),vec.end(),gLambda);
     for(auto i:vec)
       std::cout<<i<<" ";
     std::cout<<'\n';
     
     std::sort(vec2.begin(),vec2.end(),gLambda);
     for(auto i:vec2)
       std::cout<<i<<" ";
     
}