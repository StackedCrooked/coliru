#include <iostream>
#include <string>
#include <vector>
#include <map>

class MyKey
{
public:
    int i;
    int j;
    
    MyKey() : i(0), j(0) {}
    MyKey(int i_i, int i_j) : i(i_i), j(i_j) {}
    MyKey(const MyKey& r) : i(r.i), j(r.j) {}
    MyKey& operator=(const MyKey& r) {i = r.i; j = r.j; return *this;}
};

std::ostream& operator<<(std::ostream& os, const MyKey& obj)
{
    os << "[" << obj.i << "," << obj.j << "]";
    return os;
}

bool operator<(const MyKey& l, const MyKey& r)
{
    /*int lVal = l.i * 100 + l.j;
    int rVal = r.i * 100 + r.j;
    return (lVal < rVal);*/
    
}

typedef std::map<MyKey,int> MyMap;

int main()
{
    MyMap myMap;
    
    for (int ii=1; ii<=3; ii++)
    {
        for (int jj=1; jj<=3; jj++)
        {
            MyKey myKey(ii,jj);
            MyMap::const_iterator iter = myMap.find(myKey);
            if (iter == myMap.end()) {
                myMap[myKey] = ii * 100 + jj;
            }
        }
    }
    
    for (MyMap::const_iterator iter=myMap.begin(); iter!=myMap.end(); iter++)
    {
        std::cout << iter->first << " = " << iter->second << std::endl;
    }
}
