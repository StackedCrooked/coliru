#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

template<typename TContainer, typename TChar, typename TCharTraits=std::char_traits<TChar>>
std::basic_ostream<TChar, TCharTraits> &operator<<(std::basic_ostream<TChar, TCharTraits> &os, const TContainer &c){
    std::copy(std::begin(c), std::end(c), std::ostream_iterator<decltype(*std::begin(c)), TChar, TCharTraits>(os, " "));
    return os;
}

int main(){
    std::vector<int> vi(10, 0);
    std::iota(vi.begin(), vi.end(), 15);
    std::cout<<vi<<std::endl;
    return 0;
}