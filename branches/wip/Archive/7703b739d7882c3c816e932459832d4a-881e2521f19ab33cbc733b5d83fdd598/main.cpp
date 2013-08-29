    #include <iostream>
    #include <utility>
    #include <functional>
    
    template <typename... T>
    class Action {
    public:
    
      using bind_type = decltype(std::bind(std::declval<std::function<void(T...)>>(),std::declval<T>()...));
    
      template <typename... ConstrT>
      Action(std::function<void(T...)> f, ConstrT&&... args)
        : bind_(f,std::forward<ConstrT>(args)...)
      { }
    
      void act()
      { bind_(); }
    
    private:
      bind_type bind_;
    };
    
    int main()
    {
      Action<int,int> add([](int x, int y)
                          { std::cout << (x+y) << std::endl; },
                          3, 4);
    
      add.act();
      return 0;
    }
    