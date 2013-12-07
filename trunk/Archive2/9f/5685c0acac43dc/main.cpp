#include <vector>

namespace my_ns {
    using namespace std; // comment this line then line 10 won't compile anymore
    struct S {};
}
using namespace my_ns; // comment this line then lines 9 & 10 won't compile anymore

S s;
vector<int> v; // note: no std::
