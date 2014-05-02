    #include <iostream>
    #include <utility>
    #include <functional>
    
    template <class TFunc, class... TArgs>
    class Action
    {
        using bind_t = decltype(std::bind(std::declval<TFunc>(), std::declval<TArgs>()...));
        bind_t m_bound;
        
    public:
        template<class... TInnerArgs>
        Action(TFunc&& function, TInnerArgs&&... args)
        : m_bound(function, std::forward<TInnerArgs>(args)...)
        { }
        
        auto execute() -> decltype(m_bound())
        { 
            return m_bound(); 
        }
    };
    
    template<class TFunc, class... TArgs>
    Action<TFunc, TArgs...> make_action(TFunc&& func, TArgs&&... args)
    {
        return Action<TFunc, TArgs...>(std::forward<TFunc>(func), std::forward<TArgs>(args)...);
    }
    
    int main()
    {
      auto add = make_action([](std::string str)
                          { std::cout << str << std::endl; return "(o ) ( o)";},
                          "ukaz kozy");
    
      auto val = add.execute();
      
      std::cout << val << std::endl;
      return 0;
    }
    