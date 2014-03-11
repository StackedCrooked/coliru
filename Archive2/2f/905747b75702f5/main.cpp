#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template<typename R, typename ...Args>
class Signal
{
    public:
        Signal(R (*func_in)(Args...)) {func = func_in; };
        ~Signal() {};
        
        R call(Args... args) {return ((*func) (args...)); };
        R operator() (Args... args) {return ((*func) (args...)); };
        
    public:
        R (*func) (Args...);
        
};

template<typename R, typename ...Args>
Signal<R, Args...> MakeSignal(R (*func_in)(Args...)) {return Signal<R, Args...>(func_in); }

float test(float in) {return 2.0*in; }

int main()
{
    auto my_sig = Signal<float, float>(test);
    
    std::cout << "calling: " << my_sig.call(4.0) << std::endl;
    std::cout << "calling2: " << my_sig(4.0) << std::endl;
    
    auto my_sig2 = MakeSignal(test);
    
    std::cout << "calling2: " << my_sig2(4.0) << std::endl;
    
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
