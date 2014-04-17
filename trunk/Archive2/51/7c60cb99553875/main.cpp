#include <cstdlib>
#include <string>
#include <chrono>
#include <iostream>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>
using namespace std::chrono;
using namespace boost::algorithm;

template<class func_type>
void search(const std::string& heystack, const std::string& needle, const char* name, func_type&& func)
{
   auto start = high_resolution_clock::now();
   auto pos = func(heystack, needle);
   auto stop = high_resolution_clock::now();
   auto dur = duration_cast<std::chrono::nanoseconds>(stop-start);
   std::cout << name << " found " << &*pos << " in " << dur.count() << "ms\n";
}

int main() {
    const int len = 1000000;
    std::string heystack(len, '\0');
    for(int i=0; i<len-5; ++i)
        heystack[i] = 'a' + rand()%26;
    heystack[len-5] = '<';
    heystack[len-4] = '/';
    heystack[len-3] = 'p';
    heystack[len-2] = '>';
    heystack[len-1] = '\0';
    std::string needle = "</p>";
        
    search(heystack, needle, "naive", [](const std::string& heystack, const std::string& needle) -> std::string::const_iterator
        { return heystack.find(needle)+heystack.begin();});
    search(heystack, needle, "BMH  ", [](const std::string& heystack, const std::string& needle) -> std::string::const_iterator
        { return boyer_moore_horspool_search(heystack.begin(), heystack.end(), needle.begin(), needle.end());});
    search(heystack, needle, "BM   ", [](const std::string& heystack, const std::string& needle) -> std::string::const_iterator
        { return boyer_moore_search(heystack.begin(), heystack.end(), needle.begin(), needle.end());});
    search(heystack, needle, "KMP  ", [](const std::string& heystack, const std::string& needle) -> std::string::const_iterator
        { return boyer_moore_search(heystack.begin(), heystack.end(), needle.begin(), needle.end());});
}