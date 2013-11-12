#include <iostream>
using namespace std;

#define not_HAS_CONSTEXPR
#ifdef HAS_CONSTEXPR
int constexpr fakul(int n) {
    return (n == 0) ? 1 : n * fakul(n-1);
}
#else
template<int n> class fakul {
    public: static const int result = n*fakul<n-1>::result;
};
template<> class fakul<0> {
    public: static const int result = 1;
};
#endif

int main()
{
   #ifdef HAS_CONSTEXPR
   cout << fakul(6) << endl;
   #else
   cout << fakul<6>::result << endl;
   #endif
}
