    #include <memory>
    #include <iostream>
    
    template<typename T> struct shared_maker {
      template<typename... Args>
      std::shared_ptr<T> operator()(Args&&...args) const {
        return std::make_shared<T>( std::forward<Args>(args)... );
      }
    };
    template<typename T, typename Factory=shared_maker<T>>
    struct COW {
      COW( T const& t, Factory fac=Factory{} ):factory(fac), pImpl( factory(t) ) {}
      COW( Factory fac=Factory{} ):factory(fac), pImpl( factory() ) {}
      COW( COW const& ) = default;
      COW( COW && ) = default;
    private:
      Factory factory;
      std::shared_ptr<T> pImpl;
    public:
      template<typename F>
      void modify( F&& f ) {
        if (pImpl && pImpl.use_count() == 1) {
          std::forward<F>(f)(*pImpl);
        } else {
          if (!pImpl)
            pImpl=factory();
          T tmp(*pImpl);
          std::forward<F>(f)(tmp);
          pImpl = factory(std::move(tmp));
        }
      }
      T const* operator->() const { return pImpl.get(); }
      T const& operator*() const { return *pImpl; }
    };

    int main() {
      COW<int> x;
    		COW<int> y = x;
			std::cout << "x@" << &*x << " is " << *x << ",";
			std::cout << "y@" << &*y << " is " << *y << "\n";
			x.modify( [](int& i){ ++i; } );
			std::cout << "x@" << &*x << " is " << *x << ",";
			std::cout << "y@" << &*y << " is " << *y << "\n";
    }
