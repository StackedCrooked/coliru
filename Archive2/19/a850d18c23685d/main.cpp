#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
 
 long m_lLineNumber=128;
typedef std::pair<int,int> mypair;
bool comparator ( const mypair& l, const mypair& r)
   { return l.first < r.first; }
   

int main()
{
    //std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 

    mypair* myPairArr = new mypair[m_lLineNumber];
    
    for(int i=0; i< m_lLineNumber; i++)
    {
        myPairArr[i].first = fmod(0.61*m_lLineNumber*i,m_lLineNumber) ;
        myPairArr[i].second = i;
        
    }
    for (int  i= 0; i<m_lLineNumber;i++) {
        std::cout << myPairArr[i].first << " ";
    }  
        std::cout << '\n';
    std::sort(myPairArr,myPairArr + m_lLineNumber,comparator);
    //std::cout << std::end(myPairArr) << "\n " ;
    // sort using the default operator<
    
    for (int  i= 0; i<m_lLineNumber;i++) {
        std::cout << myPairArr[i].first << " ";
    }   
    std::cout << '\n';
    for (int  i= 0; i<m_lLineNumber;i++) {
        std::cout << myPairArr[i].second << " ";
    }
     std::cout << '\n';
}