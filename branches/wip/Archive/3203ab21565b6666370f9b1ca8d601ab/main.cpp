#include <vector>

template<typename T>
struct Wrap
{
    explicit Wrap(T t) : t_(t) {}
        
    //Wrap(Wrap&&) noexcept = default;
        
    Wrap(Wrap&&) = default;
    Wrap& operator=(Wrap&&) = default;
    Wrap(const Wrap&) = delete;
    Wrap& operator=(const Wrap&) = delete;
    
    T t_;
};

int main()
{
    std::vector<Wrap<int>> integers;
    integers.emplace_back(1);
}
