    #include <utility>
    #include <functional>
    
    template<class T>
    T&& unref( T&& t ){return std::forward<T>(t);}
    template<class T>
    T& unref( std::reference_wrapper<T> r ){ return r.get(); }

    template<class F>
    auto ref_clean( F&& f ) {
      return [f = std::forward<F>(f)](auto&&... args){
        return f( unref( std::forward<decltype(args)>(args) )... );
      };
    }

    #include <thread>
    #include <iostream>
    
    template <typename T>
    struct f {
      void operator() (T& result) { result = 1;}
    };

    int main() {
      int x = 0;
      auto g = ref_clean([](auto& result) { result = 2; });

      std::thread(f<int>(), std::ref(x)).join();  // COMPILES
      std::cout << x << "\n";

      std::thread(g, std::ref(x)).join();         // COMPILES
      
      std::cout << x << "\n";
    }