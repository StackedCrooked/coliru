#include <iostream>
#include <string>
#include <map>

using namespace std;

#define LEN(x) #x
#define TEST(x) #x LEN(sizeof(#x)-1)

#if defined M1 || M2 > M3\
#error ERROR
#endif

int main()
{
    //map<string, int> map1 = {make_pair("one", 1), make_pair("two", 2)};
    //map<string, int> map2 = {make_pair("two", 1), make_pair("tree", 2)};
    //copy(map1.begin(), map1.end(), inserter(map2, map2.end()));
    //for(auto elem : map2) cout << elem.first << " " << elem.second << '\n';
    cout << TEST(something) << endl;
    return 0;
}
