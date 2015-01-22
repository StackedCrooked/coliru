#include <string>
#include <iostream>
using namespace std;

template <typename T>
class Less_then {
    const T val;
public:
    Less_then(const T& v) : val(v) {}
    bool operator()(const T& x)const { return x < val; }
};

Less_then<int> lti {42};
Less_then<string> lts { "Backus" };

template<typename C, typename P>
int count(const C& c, P pred) {
    int cnt = 0;
    for (const auto& x: c) {
        if (pred(x)) {
            cnt++;
        }
    }
    return cnt++;
}

int main() {
    cout << "hi";
    return 0;
}