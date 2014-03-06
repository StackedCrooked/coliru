#include <vector>

class MyClass
{
    private: 
        std::vector<double> _data;
    public:
        template <class... Args>
        auto insert(Args&&... args) -> decltype(auto)
        {
            return _data.emplace_back(std::forward<Args>(args)...);
        }
};

int main()
{
    MyClass m;
    m.insert(2.0);
    
    return 0;
}