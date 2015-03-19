#include <iostream>
#include <utility>
using namespace std;

typedef int u32;

class CHasStringConstructor
{
private:
    u32 m_uValue;

public:
    CHasStringConstructor() : m_uValue(0) {}
    CHasStringConstructor(const string&) : m_uValue(123) {}
};

typedef char s8;
typedef s8 no[1];
typedef s8 yes[2];
//template <typename C> static yes& checkIfHasStringConstructor(decltype (C(const string&)) *);
template <typename C> static yes& checkIfHasStringConstructor(decltype (C(declval<string>())) *);
template <typename> static no& checkIfHasStringConstructor(...);

static const s8 s_iFromStringMethod = (sizeof(checkIfHasStringConstructor<CHasStringConstructor>(0)) == sizeof(yes));

int main()
{
    cout << (int)s_iFromStringMethod << endl;
}