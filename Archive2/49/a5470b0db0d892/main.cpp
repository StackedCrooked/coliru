    #include <iostream>
    #include <utility>
    #include <functional>
    
    class ExClass
    {
    private:
        int m_field;
        
    public:
        ExClass() : m_field(7) {}
        void PrintField() const { std::cout << m_field << std::endl; }
    };
    
    template <class TFunc, class... TArgs>
    class Action
    {
        using bind_type = decltype(std::bind(std::declval<TFunc>(), std::declval<TArgs>()...));
        bind_type m_bound;
        
    public:
        template<class TInnerFunc, class... TInnerArgs>
        Action(TInnerFunc&& functor, TInnerArgs&&... args)
            : m_bound(std::forward<TInnerFunc>(functor), std::forward<TInnerArgs>(args)...)
        { }
        
        auto execute() -> decltype(m_bound())
        { 
            return m_bound(); 
        }
    };
    
    template<class TFunc, class... TArgs>
    Action<TFunc, TArgs...> make_action(TFunc&& functor, TArgs&&... args)
    {
        return Action<TFunc, TArgs...>(std::forward<TFunc>(functor), std::forward<TArgs>(args)...);
    }
    
    int main()
    {
        ExClass cl = ExClass();
        
        // causes errors
        auto action1 = make_action(&ExClass::PrintField, cl);
        action1.execute();
        
        int a = 7;
        auto action2 = make_action([&](int& x) { x += 2; std::cout << x << std::endl; }, std::ref(a));
        action2.execute();
        action2.execute();
        
        return 0;
    }