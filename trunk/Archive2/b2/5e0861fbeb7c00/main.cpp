#include <string>
using std::string;

struct employee {
    string name_;
    
template <class String>
void set_name(String &&name) {
    name_ = {std::forward<String>(name)};
}
  
};


template <class String>
auto foo(employee& e, String&& name) 
-> decltype(e.set_name(std::forward<String>(name)), void()) {
    e.set_name(std::forward<String>(name));
}

int main() {
    employee e;
    foo(e, 'a');
    foo(e, "a");
    // foo(e, 10); // error
}
