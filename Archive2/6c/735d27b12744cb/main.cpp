#include <string>
#include <iostream>
#include <map>
 
int main()
{
    typedef int Data;
    typedef Data* pData;
    typedef std::map<const std::string, pData>  MyMap;

    // create map
    MyMap* myMap = new MyMap();
    
    // create object 
    pData vToto = new Data(42);
    
    // insert 
    myMap->operator[]("toto") = vToto;
    
    //retrieve
    std::cout << "toto equals " << myMap->operator[]("toto") << std::endl;
    
    //delete
    delete myMap;
    delete vToto;
    
    return 0;
}