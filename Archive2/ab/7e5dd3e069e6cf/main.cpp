#include <iostream>
#include <string>
#include <map>

using namespace std;


#ifdef NDEBUG
#define DEBUG(var)
#else
#define DEBUG(var) { std::cout << #var << ": " << (var) << std::endl; }
#endif

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& out, const std::map<T1,T2> &M) {
    out << "{ ";
    for (auto item:M) out << item.first << "->" << item.second << ", ";
    out << "}";
    return out;
}

int main() {
    std::map<std::string,int> age = { {"Joe",47}, {"Bob",22}, {"Laura",19} };
    DEBUG(age);
}

