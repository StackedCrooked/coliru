#include <functional>

void set_callback(std::function<void()>) {}
void set_callback(std::function<void(int)>) {}

// let's try doing it!
namespace my {
    
template<typename Sig>
struct function {
    template<typename Function>
    function(Function) {}
};

void set_callback(function<void()>) {}
void set_callback(function<void(int)>) {}

} // my

int main()
{
    // fine
    set_callback([] {});
    
    // how do they do it?!
    // error: call of overloaded 'set_callback(main()::<lambda()>)' is ambiguous
    // my::set_callback([] {});
}