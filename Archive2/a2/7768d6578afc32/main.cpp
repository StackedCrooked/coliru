#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
template<typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a+b)
{
    return a+b;
}


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;


auto k = 10; //k is int

std::vector<int> v;
v.push_back(8);

vector<int>::iterator it = begin(v);
auto it2 = begin(v);
*it2 = 9;

cout << v <<endl;


map<int, int> map1;
auto it3 = begin(map1);
map<int, int>::iterator it4;
auto it5 = map1.cbegin();

auto i1 = add(11, 11);
auto d2 =  add(11.0, 13);
auto s1= add(string("hehe"), string("hiih"));

cout << i1 <<" "<<d2 <<s1;

auto x = v.size();
unsigned x2 = v.size(); //win32 -> 32bit, win64: unsigned 32bint, size() 64bit.

//itt ne:
auto intVariable = {1};
vector<bool> vectBool;

auto it = vectBool.begin();
}
