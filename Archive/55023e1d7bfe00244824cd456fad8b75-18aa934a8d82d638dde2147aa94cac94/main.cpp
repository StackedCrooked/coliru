#include <memory>
#include <functional>
#include <iostream>

//@@@TODO:
//std::equal_to
//return types
//specialize switch_any for `const char(&)[N]`

template<class othercases>
struct switch_case_type : othercases {
    typedef typename othercases::value_type value_type;
    typedef std::function<void()> func_type;
    
    switch_case_type(value_type label, func_type function, othercases rest) :othercases(std::move(rest)), l(std::move(label)), f(std::move(function)) {}
    switch_case_type(switch_case_type&& rhs) :othercases(std::move(rhs)), l(std::move(rhs.l)), f(std::move(rhs.f)) {}
    ~switch_case_type() { if (this->s) {do_switch(*(this->s)); this->s = nullptr;} }
    void do_switch(const value_type& switch_value) const {if (switch_value == l) f(); else othercases::do_switch(switch_value);}
    
    template<class U>
    auto case_(U&& label, func_type function) -> switch_case_type<decltype(std::declval<othercases>().case_(std::forward<U>(label),std::move(function)))>
    {return {std::move(l), std::move(f), othercases::case_(std::move(label),std::move(function))};}
    switch_case_type&& default_(func_type function) /*&&*/ {this->d = std::move(function); return std::move(*this);}
private:
    value_type l;
    std::function<void()> f;
};

template<class T>
struct switch_any_type {
    typedef T value_type;
    typedef std::function<void()> func_type;
    
    switch_any_type() :s(nullptr) {}
    explicit switch_any_type(const T& switch_value) :s(&switch_value) {}
    switch_any_type(switch_any_type&& rhs) :s(rhs.s),d(std::move(rhs.d)) {rhs.s = nullptr;}
    ~switch_any_type() {if (s) d();}
    void do_switch(const value_type&) const {d();}
    
    //switch_any_type& default_(func_type function) & {this->d = std::move(function); return *this;}
    switch_any_type&& default_(func_type function) /*&&*/ {this->d = std::move(function); return std::move(*this);}
    switch_case_type<switch_any_type<T>> case_(value_type label, func_type function) 
    {return {std::move(label), std::move(function), std::move(*this)};}
protected:
    const T* s;
    std::function<void()> d;
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
            
        static auto myswitch0 = switch_any_type<std::string>() 
            .case_("A", [&]{std::cout << "A\n";}) 
            .default_([&]{std::cout << "B\n";})   
            ;
        myswitch0.do_switch("A");
        myswitch0.do_switch("B");
          
        static auto myswitch1 = switch_any_type<std::string>()
            .case_("MooingDuck", [&]{std::cout << "AWESOME\n";})
            .case_("CatPlusPlus", [&]{std::cout << "CRANKY DRUNKARD\n";})
            .case_("MooingDuck", [&]{std::cout << "WTFBUG\n";})
            ;
        myswitch1.do_switch(name);
        myswitch1.do_switch("CatPlusPlus");
        myswitch1.do_switch("Xeo");
        
        
    } catch(std::bad_function_call& bfc) {
        std::cout << "invalid name!";
    }
}
