#include <iostream>
#include <utility>

    template<typename T> using type=T;
    
    template<typename F, typename X=void*>
    struct callback_t {
      F f;
      operator X() const { return X(&f); }
      template<typename R, typename...Args>
      operator type<R(*)(X, Args...)>() const {
        return []( X x, Args... args )->R {
          F* f = (F*)(x);
          return (*f)(std::forward<Args>(args)...);
        };
      }
    };
    template<typename X=void*, typename F>
    callback_t<F,X> make_callback( F f ) {
      return {std::forward<F>(f)};
    }

    typedef void(*pfun)(void*, int);
    void call_pfun( pfun f, void* p) {
      for (int i = 0; i < 3; ++i)
        f( p, i );
    }
    int main()
    {
      int y = 7;
      auto callback = make_callback([y]( int x ) { std::cout << x+y << "\n"; });
      call_pfun( callback, callback );
    }