#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <cmath>

// the shared_ptr<void> idiom
typedef std::shared_ptr<void> shared_any;
// the unique_ptr<void> idiom
typedef std::unique_ptr<void, std::function<void(void*)>> unique_any;

template<class T>
struct smart_default_delete {
    std::default_delete<T> delegate;
    
    void operator()(T* ptr) noexcept { delegate(ptr); }
    void operator()(void* ptr) noexcept { delegate(static_cast<T*>(ptr)); }
};

template<class T, class ...Args>
std::unique_ptr<T, smart_default_delete<T> > make_unique(Args&&... args) {
    return std::unique_ptr<T, smart_default_delete<T> >{ new T(std::forward<Args>(args)...) };
}

struct printer {

    static int global_id;
    int id;
    
#define BODY std::cout << id << ": " << __PRETTY_FUNCTION__ << std::endl;

    printer(): id(global_id++) { BODY }
    printer(const printer&): id(global_id++){ BODY }
    printer(printer&&): id(global_id++){ BODY }
    ~printer(){ BODY }
    
    printer& operator=(const printer&){ BODY return *this; }
    printer& operator=(printer&&){ BODY return *this; }

#undef BODY

};

int printer::global_id = 0;

int main()
{
    {
        shared_any one = std::make_shared<printer>(); // printer()#1
        one = std::make_shared<printer>(); // printer#2; ~printer()#1
    } // ~printer#2
    
    {
        auto one = make_unique<printer>(); // printer()#3
        unique_any two { std::move(one) }; // nothing (moving unique_ptr)
        unique_any three = make_unique<printer>(); // printer()#4
        three = std::move(two); // ~printer()#4; nothing (moving printer#3 from two to three)
    } // ~printer()#3

}
