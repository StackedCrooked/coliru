#include <iostream>
#include <type_traits>

using namespace std;

const int i = 1;
const int j = 2;
struct x
{
   int x;
};

namespace y
{
   int i[i];
   int j = j;
   x x;
   int y = x.x;
}

ostream& operator << (ostream& os, const x& x) {
    return os << "X[" << x.x << "]";
}

template <typename T, size_t N>
typename enable_if<!is_same<T,char>::value,ostream&>::type
operator << (ostream& os, const T (&array)[N]) {
    os << "{ ";
    for(size_t i = 0; i < N; ++i) {
        if (i != 0) {
            os << ", ";
        }
        os << array[i];
    }
    os << " }";
    return os;
}

int main() {
    #define P(name) cout << #name " = " << (name) << endl;
    P(::i);
    P(::j);
    P(y::i);
    P(y::j);
    P(y::x);
    P(y::y);
}
