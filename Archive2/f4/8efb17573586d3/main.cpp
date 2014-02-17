#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::string s1 = "Hello";
    std::string s2 = "World";
    
    std::sort(begin(s1), end(s1));
    std::sort(begin(s2), end(s2));
    
    std::string s3;
    std::set_intersection(begin(s1), end(s1), begin(s2), end(s2), std::back_inserter(s3));
    std::cout << s3.size() << ":" << s3;
}
