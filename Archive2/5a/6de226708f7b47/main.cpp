#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, std::pair<T1, T2> const &mp) {
  return (out << "(" << mp.first << ", " << mp.second << ")");
}

template<typename Iterator>
void print(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        cout << *begin << endl;
        ++begin;
    }
}

int main()
{
    vector<int> noVec = { 1, 2, 3 };

    print(noVec.begin(), noVec.end());

    map<int, int> nosMap;
    nosMap[0] = 1;
    nosMap[1] = 2;
    nosMap[3] = 3;

    print(nosMap.begin(), nosMap.end());

    return 0;
}