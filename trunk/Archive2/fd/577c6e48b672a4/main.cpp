#include <iostream>
#include <assert.h>

    typedef unsigned long long ull;
    template<ull mod>
    struct fast_fact {
      ull m( ull a, ull b ) const {
        ull r = (a%mod)*(b%mod);
        // std::cout << "multiplying " << r << '=' << a << '*' << b << '\n';
        return r;
      }
      template<class...Ts>
      ull m( ull a, ull b, Ts...ts ) const {
        return m( m( a, b )%mod, ts... );
      }
      ull double_fact( ull x ) const {
        // std::cout << x << "!!\n";
        ull ret = 1;
        for (ull i = 1; i < x; i+=2) {
          ret = m(i,ret);
        }
        return ret%mod;
      }
      ull const* get_pows() const {
        // std::cout << "calculating powers of 2\n";
        static ull retval[ sizeof(ull)*8 ] = {2};
        for (int i = 1; i < sizeof(ull)*8; ++i) {
          retval[i] = m(retval[i-1],2);
        }
        return retval;
      }
      ull pow_2( ull x ) const {
        static ull const* pows = get_pows();
        // std::cout << "calculating 2^" << x << '\n';
        ull retval = 1;
        for (int i = 0; x; ++i, (x=x/2)){
          if (x&1) retval = m(retval, pows[i]);
        }
        // std::cout << "= " << retval%mod << '\n';
        return retval%mod;
      }
      ull operator()( ull x ) const {
        if (x==0) return 1;
        // std::cout << "calculating " << x << "!\n";
        // odd case:
        if (x&1) return m( (*this)(x-1), x )%mod;
        return m( double_fact(x), pow_2(x/2), (*this)(x/2) );
      }
    };
    template<ull mod>
    ull factorial_mod( ull x ) {
      return fast_fact<mod>()(x);
    }
    
int main() {
    std::cout << factorial_mod< 1000000009ull >(32571) << '\n';
}