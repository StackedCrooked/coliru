#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

template<class L, class R>
std::istream& operator>>(std::istream& i, std::pair<L,R>& d) 
{return i>>d.first>>d.second;}

int main(){
    std::vector<std::pair<int,int>> myvector; 
    std::ifstream filestream("data-for-union-find.txt");
    using ::operator>>;
    std::copy(
        std::istream_iterator<std::pair<int,int>>(filestream),
        std::istream_iterator<std::pair<int,int>>(),
        std::back_inserter(myvector));
    std::cout << "success";
}