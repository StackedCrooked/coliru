#include <iostream>
#include <string>
#include <vector>


// Quiz: what's wrong with this code? (and how can it be fixed?)


/**
 * represents an "optional" value and provides pointer-like semantics
 */
template<typename T>
struct optional
{
    optional() : t_(), valid_() {}    
    
    optional(const T& t) : t_(t), valid_(true) {}
    
    operator bool() const { return valid_; }
    
    const T& operator*() const { return t_; }
    T& operator*() { return t_; }
    
private:
    T t_;
    bool valid_;
};


int main()
{
    std::cout << optional<int>(0) << std::endl;
}
