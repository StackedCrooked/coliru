#include <vector>
#include <iostream>
#include <algorithm>

class example
{
private:
    int m_sum;
public:
    template <class... Ts> example(Ts&&... vs) : m_sum(compute_sum(vs...)) { }

    int get_sum() const
    {
        return m_sum;
    }
    
private:
    template<typename Ts1>
    Ts1 compute_sum(const Ts1& val) { return val; } // termination
 
    template<typename Ts1, typename... Ts>
    Ts1 compute_sum(const Ts1& arg1, const Ts&... args)
    {
        return arg1 + compute_sum(args...); 
    }
};

int main() {

    example e = { 1, 2, 3, 4};
    std::cout << e.get_sum();
    return 0;
}