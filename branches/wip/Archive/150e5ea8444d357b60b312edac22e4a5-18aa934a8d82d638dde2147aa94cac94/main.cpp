#include <unordered_map>
#include <functional>

template<class T>
class switch_any_type {
private:
    const T* v;
public:
    struct case_body {
        switch_any_type& operator()(std::function<void()>&& f) {*b=std::move(f); return *p;}
    private:
        friend switch_any_type<T>;
        case_body(switch_any_type* parent, std::function<void()>& body) :p(parent),b(&body){}
        switch_any_type* p;
        std::function<void()>* b;
    };
    std::unordered_map<T, std::function<void()>> cases;
    
    explicit switch_any_type(const T& switch_value) :v(&switch_value){}
    ~switch_any_type() {if (v) cases[*v]();}
    case_body case_(const T& case_value) {return case_body(this,cases[case_value]);}
    
    switch_any_type() :v(nullptr) {}  //for less idiomatic but more efficient usage
    void do_switch(const T& v) {cases[v]();}
};
template<class T>
switch_any_type<T> switch_any(const T& switch_value) {return switch_any_type<T>(switch_value);}

#include <string>
#include <iostream>
int main() {
    try {
        std::string name="MooingDuck";
        
        switch_any(name)
            .case_("MooingDuck")([&]{std::cout << "AWESOME\n";})
            .case_("CatPlusPlus")([&]{std::cout << "CRANKY DRUNKARD\n";})
            ;      
          
        static auto myswitch = switch_any_type<std::string>()
            .case_("MooingDuck")([&]{std::cout << "AWESOME\n";})
            .case_("CatPlusPlus")([&]{std::cout << "CRANKY DRUNKARD\n";})
            ;
        myswitch.do_switch(name);
        myswitch.do_switch("CatPlusPlus");
        myswitch.do_switch("Xeo");
        
    } catch(std::bad_function_call& bfc) {
        std::cout << "invalid name!";
    }
}
