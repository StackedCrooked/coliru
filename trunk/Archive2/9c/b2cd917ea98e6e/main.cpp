#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <iterator>

int main()
{
    std::list<int> data;
    for (int i= 1; i <= 20; i++) data.push_back(i);
    
    std::ostringstream str;
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<int>(str, ","));
              
    std::cout << str.str() << std::endl;
    
    // without trailing comma
    std::cout << str.str().substr(0, str.str().size() -1) << std::endl;
}
