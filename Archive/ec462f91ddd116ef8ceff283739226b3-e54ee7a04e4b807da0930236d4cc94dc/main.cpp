#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

class test {
    struct con {
        string s1;
        string s2;
    };
public:
    void somefunc();

private:
    bool pred(con c1, con c2) const;
    vector<con> vec;
};

void test::somefunc()
{
    vector<con> v;
    vector<con>::iterator it = find_first_of(vec.begin(), vec.end(), v.begin(), v.end(),
        std::bind(&test::pred, this, std::placeholders::_1, std::placeholders::_2));
}

bool test::pred(con c1, con c2) const
{
    return 0;
}

int main() { } 