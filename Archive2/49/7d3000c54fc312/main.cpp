template<typename def, typename inner = typename def::type>
class like_enum : public def
{
    typedef inner type;
    inner val;

public:
    like_enum() {}
    like_enum(type v) : val(v) {}
    operator type () const { return val; }

    friend bool operator == (const like_enum & lhs, const like_enum & rhs) { return lhs.val == rhs.val; }
    friend bool operator != (const like_enum & lhs, const like_enum & rhs) { return lhs.val != rhs.val; }
    friend bool operator <  (const like_enum & lhs, const like_enum & rhs) { return lhs.val <  rhs.val; }
    friend bool operator <= (const like_enum & lhs, const like_enum & rhs) { return lhs.val <= rhs.val; }
    friend bool operator >  (const like_enum & lhs, const like_enum & rhs) { return lhs.val >  rhs.val; }
    friend bool operator >= (const like_enum & lhs, const like_enum & rhs) { return lhs.val >= rhs.val; }
};

namespace cpp03
{
    struct KlingonType
    {
        enum type
        {
            Qapla,
            Ghobe,
            Highos
        };
    };

    typedef like_enum<KlingonType> Klingon;
}

namespace cpp11
{
    enum class Klingon
    {
        Qapla,
        Ghobe,
        Highos
    };
}

#include <iostream>
#include <iomanip>
#include <type_traits>
using namespace std;

int main() {
    cout << boolalpha
         << "is_pod<Klingon>::value\n"
         << "  C++03: " << is_pod<cpp03::Klingon>::value << '\n'
         << "  C++11: " << is_pod<cpp11::Klingon>::value << '\n';

    cout << "sizeof<Klingon>::value\n"
         << "  C++03: " << sizeof(cpp03::Klingon) << '\n'
         << "  C++11: " << sizeof(cpp11::Klingon) << '\n';
}