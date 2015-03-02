#include <iostream>
#include <string>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::map<T,T>& vec)
{
    for (typename std::map<T,T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        os << it->first<< " " << it->second <<std::endl;
    }
    return os;
}

int main()
{
    using namespace std;
    map<int,int> words;
    for (int i=0;i<100;++i) words.insert(make_pair(i,i+3));
    for (map<int,int>::iterator it = words.begin(); it != words.end(); ++it){ if(it->first % 4 == 0) { words.erase(it);++it; words.erase(it);}}
    std::cout << words << std::endl;
}
