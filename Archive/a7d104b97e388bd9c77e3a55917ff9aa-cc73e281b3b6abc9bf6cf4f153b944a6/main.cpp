#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

bool is_anagram4(const std::string &s1, const std::string &s2)
{
    if (s1.length() != s2.length()) return false;
    int arr[256] = {};
    for(std::string::size_type i = 0; i < s1.length(); i++) {
      arr[(unsigned)s1[i]]++;
      arr[(unsigned)s2[i]]--;
    }
    for(auto i : arr) {
        if (i) 
            return false;
    } 
    return true;
}

unsigned anagram4test(const std::vector<std::string>& data) {
    unsigned r=0;
    for(unsigned i=0; i<data.size(); ++i) {
        for(unsigned j=i+1; j<data.size(); ++j) {
            if (is_anagram4(data[i], data[j]))
                ++r;
        }
    }
    return r;
}

unsigned anagram6test(std::vector<std::string> data) {
    unsigned r=0;
    for(unsigned i=0; i<data.size(); ++i)
        std::sort(data[i].begin(), data[i].end());
    for(unsigned i=0; i<data.size(); ++i) {
        for(unsigned j=i+1; j<data.size(); ++j) 
            if(data[i]==data[j])
                ++r;
    }
    return r;
}


static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

template<class T>
void anagramtest(const char* name, T func, const std::vector<std::string>& data)
{
    unsigned long long time = rdtsc();
    unsigned res = func(data);
    time = rdtsc()-time;
    cout << "Function" << left << setw(15) << name 
     << " time: " << right << setw(8) << time 
     << " Res: " << res << endl;
}
#define TEST(x) anagramtest(#x, x, data)



int main()
{
    //because I'm too lazy to parse it out myself
    std::stringstream ss("Parts of the world have sunlight for close to 24 hours during summer. Dan went to the north pole to lead an expedition during summer. He had a strap on his head to identify himself as the leader. Dan had to deal with the sun never going down for 42 consecutive days and his leadership strap soon became a blindfold. He wondered what kind of traps lay ahead of him.");
    std::istream_iterator<std::string> first(ss), last;
    std::vector<std::string> data(first, last);
    
    TEST(anagram4test);
    TEST(anagram4test);
    TEST(anagram6test);
    TEST(anagram6test);
    TEST(anagram4test);
    TEST(anagram4test);
    
    return 0;
}