#include <unordered_map>
#include <memory>
#include <functional>

template<class othercases>
struct switch_case_type : othercases {
    typedef typename othercases::value_type value_type;
    typedef std::function<void()> func_type;
    typedef switch_case_type<switch_case_type<othercases>> child_type;
    
    switch_case_type(othercases rest, value_type label, func_type function) 
    :othercases(std::move(rest)), l(std::move(label)), f(std::move(function)) {}
    switch_case_type(switch_case_type&& rhs) 
    :othercases(std::move(rhs)), l(std::move(rhs.l)), f(std::move(rhs.f)) {}
    ~switch_case_type() {
        if (this->s && *(this->s) == l) {
            f();
            this->s = nullptr;
        }
    }
    child_type case_(value_type label, func_type function) 
    {return {std::move(*this), std::move(label), std::move(function)};}
    switch_case_type default_(func_type function) 
    {this->d = function; return *this;}
private:
    value_type l;
    std::function<void()> f;
};
template<class T>
struct switch_any_type {
    typedef T value_type;
    typedef std::function<void()> func_type;
    typedef switch_case_type<switch_any_type<T>> child_type;
    
    switch_any_type() 
    :s(nullptr) {}
    explicit switch_any_type(const T& switch_value) 
    :s(&switch_value) {}
    switch_any_type(switch_any_type&& rhs) 
    :s(rhs.s) {rhs.s = nullptr;}
    ~switch_any_type() {
        if (this->s) {
            f();
            s = nullptr;
        }
    }
    child_type case_(value_type label, func_type function) 
    {return {std::move(*this), std::move(label), std::move(function)};}
    switch_any_type default_(func_type function) 
    {this->d = function; return *this;}
protected:
    const T* s;
    std::function<void()> f;
};
template<class T>
switch_any_type<T> switch_any(const T& switch_value) 
{return switch_any_type<T>(switch_value);}


#include <string>
#include <iostream>
int main() {
    try {
        std::string name="MooingDuck";
        
        switch_any(name)
            .case_("MooingDuck", [&]{std::cout << "AWESOME\n";})
            .case_("CatPlusPlus", [&]{std::cout << "CRANKY DRUNKARD\n";})
            ;      
          
        //static auto myswitch = switch_any_type<std::string>()
        //    .case_("MooingDuck", [&]{std::cout << "AWESOME\n";})
        //    .case_("CatPlusPlus", [&]{std::cout << "CRANKY DRUNKARD\n";})
        //    ;
        //myswitch.do_switch(name);
        //myswitch.do_switch("CatPlusPlus");
        //myswitch.do_switch("Xeo");
        
    } catch(std::bad_function_call& bfc) {
        std::cout << "invalid name!";
    }
}
