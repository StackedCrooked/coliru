
#include <iostream>

template<class F>
struct copy_assignable_function {

    union { F f; };

    copy_assignable_function(F f):
        f(f){}
    copy_assignable_function(const copy_assignable_function& other): 
        f(other.f) {}

    ~copy_assignable_function() {
        f.~F();
    }

    copy_assignable_function& operator=(const copy_assignable_function& other) {
        f.~F();
        new(&f)F(other.f);
        return *this;
    }

    template<class ...Args>
    auto operator()(Args&&... args) const -> decltype(f(std::forward<Args>(args)...)){
        return f(std::forward<Args>(args)...);
    }

};

int main(){
    auto lam = [](auto&& x){ return x + 2; };
    copy_assignable_function<decltype(lam)> caf (lam);
    
    std::cerr << caf(42) << std::endl;
}