struct move_only
{
    move_only() = default;
    move_only(move_only&&) = default;
    move_only& operator= (move_only&&) = default;
    move_only(move_only const&) = delete;
    move_only& operator= (move_only const&) = delete;
    ~move_only() = default;
};

#include <iostream>

struct move_only_fot : move_only
{
    void operator() () const { std::cout << "meow!\n"; }
};

#include <functional>
#include <utility>

template<class F>
class function_mo : private std::function<F>, private move_only
{
    template<class Fun>
    struct hack
    {
        Fun f;
        
        hack(Fun p) : f(std::move(p)) {}
        hack(hack&&) = default;
        hack(hack const&) { throw -1; }
        hack& operator= (hack&&) = default;
        hack& operator= (hack const&) { throw -1; }
        ~hack() = default;
        
        template<class... Args>
        auto operator() (Args&&... args)
        -> decltype( f(std::forward<Args>(args)...) )
        {
            return f(std::forward<Args>(args)...);
        }
    };
    
public:
    template<class Fun>
    function_mo(Fun fun)
        : std::function<F>( hack<Fun>(std::move(fun)) )
    {}
    
    using std::function<F>::operator();
};

int main()
{
    auto f = move_only_fot{};
    auto ff = function_mo<void()>{std::move(f)};
    ff();
}