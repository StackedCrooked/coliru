#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    std::string s = "foo $deli: baa $deli: don't $deli: matter";
    std::string::const_iterator it_begin = s.begin();
    std::string::const_iterator it_end = s.end();
    std::string del = "$deli";
    
    while ( (it_begin = std::search(it_begin, it_end, del.begin(), del.end())) != it_end ) {
        it_begin += del.size();
        std::cout << std::string( it_begin, it_end ) << '\n';
    }
}