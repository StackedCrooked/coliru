    #include <iostream>
    #include <utility>
    #include <functional>
    
    template <class TFunc, class... TArgs>
    class Action
    {
        using bind_t = decltype(std::bind(std::declval<TFunc>(), std::declval<TArgs>()...));
        bind_t m_bind;
        
    public:
        template<class... TInnerArgs>
        Action(TFunc&& function, TInnerArgs&&... args)
        : m_bind(function, std::forward<TInnerArgs>(args)...)
        { }
        
        void execute() { m_bind(); }
    };
    
    template<class TFunc, class... TArgs>
    Action<TFunc, TArgs...> make_action(TFunc&& func, TArgs&&... args)
    {
        return Action<TFunc, TArgs...>(std::forward<TFunc>(func), std::forward<TArgs>(args)...);
    }
    
    int main()
    {
      auto add = make_action([](int x, int y)
                          { std::cout << (x+y) << std::endl; },
                          3, 4);
    
      add.execute();
      return 0;
    }
    