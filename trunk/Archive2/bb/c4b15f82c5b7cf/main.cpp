#include <future>
#include <iostream>
#include <chrono>
using namespace std::literals;

    template<class T>
    struct ready_future_t {
      template<class...Us>
      std::future<T> operator()( Us&&...us ) const {
        std::promise<T> p;
        p.set_value({std::forward<Us>(us)...});
        return p.get_future();
      }
    };
    template<>
    struct ready_future_t<void> {
      using T=void;
      template<class...Us>
      std::future<T> operator()( Us&&...us ) const {
        std::promise<T> p;
        p.set_value();
        return p.get_future();
      }
    };
    template<class T, class...Us>
    std::future<T> ready_future(Us&&...us){
      return ready_future_t<T>{}(std::forward<Us>(us)...);
    }
    template<class U>
    struct convert_future_t {
      template<class T>
      std::future<U> operator()( std::future<T>&& f ) const {
        if (f.wait_for(0ms)==std::future_status::ready)
          return ready_future<U>(f.wait());
        return std::async(std::launch::deferred,
          [f=std::move(f)]()->U{ return f.wait(); }
        );
      }
    };
    template<>
    struct convert_future_t<void> {
      template<class T>
      std::future<void> operator()( std::future<T>&& f ) const {
        if (f.wait_for(0ms)==std::future_status::ready)
          return ready_future<void>();
        return std::async(std::launch::deferred,
          [f=std::move(f)]()->void{ f.wait(); }
        );
      }
    };

    template<class U, class T>
    std::future<U> convert_future( std::future<T>&& f ) {
      return convert_future_t<U>{}(std::move(f));
    }

int main() {
    std::future<int> f1 = ready_future<int>(3);
    std::future<void> f2 = convert_future<void>(std::move(f1));
    f2.wait();
}