#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std::placeholders;
using namespace std;

struct MyType {};
struct MyType2 {};

ostream& operator<<(ostream &os, const MyType &n)
{
    cout << "MyType" << endl;
    return os;
}

ostream& operator<<(ostream &os, const MyType2 &n)
{
    cout << "MyType2" << endl;
    return os;
}

int main()
{
    std::vector<MyType> vec;
    MyType mt;
    vec.push_back(mt);

    std::for_each(vec.begin(), vec.end(), [](const MyType &mt) {cout << mt;});  // this works
    std::for_each(vec.begin(), vec.end(), std::bind(static_cast<ostream&(&)(ostream&, const MyType&)>(::operator<<), std::ref(std::cout), _1));  // this does nothing !

    return 0;
}
