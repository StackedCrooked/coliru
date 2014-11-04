    #include <iostream>
    #include <vector>
    #include <utility>
    #include <functional>
    #include <tuple>
    
    template<typename ... TParam>
    class Signal
    {
    private:
        std::vector<std::function<void(TParam...)>> m_withArgs;
        std::vector<std::function<void()>>          m_withoutArgs;
        
    public:
        void AddListener(std::function<void(TParam...)> listener)
        {
            m_withArgs.push_back(listener);
        }
        
        void AddListener(std::function<void()> listener)
        {
            m_withoutArgs.push_back(listener);
        }
        
        void Dispatch(TParam... parameters)
        {
            for (auto& listener : m_withArgs)
                listener(parameters...);
                
            for (auto& listener : m_withoutArgs)
                listener();
        }
    };
    
    void oneArgHandler(int);
    void twoArgHandler(int, int);
    void noArgHandler();
    
    int main()
    {
        Signal<int, int> sig;
        sig.AddListener(twoArgHandler);
        sig.AddListener([](int a, int b) { oneArgHandler(a); });
        sig.AddListener(noArgHandler);
        
        sig.Dispatch(22, 12);
    }
    
    void twoArgHandler(int unused, int age)
    {
        std:: cout << "I like to rape " << age << " years old girls." << std::endl;
    }
    
    void oneArgHandler(int penisLength)
    {
        std::cout << "My penis is " << penisLength << "cm long." << std::endl;
    }
    
    void noArgHandler()
    {
        std::cout << "I'm sure yours is shorter!" << std::endl;
    }