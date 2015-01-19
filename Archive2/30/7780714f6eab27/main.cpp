#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main(){
    std::vector<int> vec={1,2,3,4};
    std::vector<int> out;
    std::partial_sum(vec.begin(),vec.end(),std::back_inserter(out));
//
//out[0]=vec[0];                          
//out[1]=vec[0]+vec[1];
//out[2]=vec[0]+vec[1]+vec[2];
//out[3]=vec[0]+vec[1]+vec[2]++vec[3];
    for(auto elem:out)
       std::cout<<elem<<" ";
}