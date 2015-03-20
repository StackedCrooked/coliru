#include <iostream>
#include <assert.h>

    typedef unsigned long long ull;

template<ull mod>
ull fact2(ull n)
{
    ull result = 1;
    for (ull i = 2; i <= n; ++i) {
        result = (result * i) % mod;
    }
    return result;
}

    template<ull mod>
    struct fast_fact {
      ull m( ull a, ull b ) const {
        ull r = (a*b)%mod;
        // std::cout << "multiplying " << r << '=' << a << '*' << b << '\n';
        return r;
      }
      template<class...Ts>
      ull m( ull a, ull b, Ts...ts ) const {
        return m( m( a, b ), ts... );
      }
      ull double_fact( ull x ) const {
        ull ret = 1;
        for (ull i = 3; i < x; i+=2) {
          ret = m(i,ret);
        }
//        std::cout << ret << '=' << x << "!!\n";
        return ret;
      }
      ull const* get_pows() const {
        // std::cout << "calculating powers of 2\n";
        static ull retval[ sizeof(ull)*8 ] = {2%mod};
        for (int i = 1; i < sizeof(ull)*8; ++i) {
          retval[i] = m(retval[i-1],retval[i-1]);
        }
        return retval;
      }
      ull pow_2( ull x ) const {
        static ull const* pows = get_pows();
//        std::cout << "calculating 2^" << x << '\n';
        ull retval = 1;
        for (int i = 0; x; ++i, (x=x/2)){
          if (x&1) retval = m(retval, pows[i]);
        }
//        std::cout << "= " << retval%mod << '\n';
        return retval;
      }
      ull operator()( ull x ) const {
        x = x%mod;
        if (x==0) return 1;
        // std::cout << "calculating " << x << "!\n";
        // odd case:
        ull result = 1;
        if (x&1) result = m( (*this)(x-1), x );
        else result = m( double_fact(x), pow_2(x/2), (*this)(x/2) );
//        if (result != fact2<mod>(x))
 //           std::cout << fact2<mod>(x) << " != " << result << " == " << x << "!\n";
        return result;
      }
    };
    template<ull mod>
    ull factorial_mod( ull x ) {
      return fast_fact<mod>()(x);
    }
    
int main() {
    std::cout << factorial_mod< 1000000007ull >(50000) << '\n';
}