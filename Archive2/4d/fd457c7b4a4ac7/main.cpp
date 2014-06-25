#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
 
 
class Test {
public:
    Test(int n):m_n(n) {}
    
    int getN() { return m_n;};

private:
    int m_n;
};

int main()
{
    
    
    std::vector<Test> myvec;
    myvec.reserve(100);
    
    myvec[10]=Test(50);
    
    std::cout << myvec[10].getN() << std::endl;
    

}