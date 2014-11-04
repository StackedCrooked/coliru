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
    
    void argHandler(int);
    void noargHandler();
    
    int main()
    {
        Signal<int> sig;
        sig.AddListener(argHandler);
        sig.AddListener(noargHandler);
        
        sig.Dispatch(22);
    }
    
    void argHandler(int penisLength)
    {
        std::cout << "My penis is " << penisLength << "cm long" << std::endl;
    }
    
    void noargHandler()
    {
        std::cout << "I'm sure yours is shorter!" << std::endl;
    }