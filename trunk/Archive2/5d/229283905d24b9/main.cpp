#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
 
 
typedef std::pair<int,int> mypair;
bool comparator ( const mypair& l, const mypair& r)
   { return l.first < r.first; }
int main()
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
    mypair myPairArr[10];
    for(int i=0; i< 10; i++)
    {
        myPairArr[i].first = -i ;
        myPairArr[i].second = i;
        
    }
    std::sort(std::begin(myPairArr),std::end(myPairArr),comparator);
 
    // sort using the default operator<
    std::sort(s.begin(), s.end());
    for (int  i= 0; i<10;i++) {
        std::cout << myPairArr[i].first << " ";
    }   
    std::cout << '\n';
    for (int  i= 0; i<10;i++) {
        std::cout << myPairArr[i].second << " ";
    }
     std::cout << '\n';
}