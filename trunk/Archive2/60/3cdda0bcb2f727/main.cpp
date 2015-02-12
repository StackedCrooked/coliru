#include <type_traits>
#include <iostream>
#include <unordered_map>

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <math.h>
using namespace std;

struct S {
    int x;
};

int main() {
    S s1;
    S s2{};
    S s3;
    cout << s1.x << " " << s2.x << " " << s3.x << endl;
}