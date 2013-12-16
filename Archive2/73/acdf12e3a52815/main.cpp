#include <initializer_list>
#include <type_traits>


template<typename T>
void func(T arg) {
}


int main() {
    auto init_list = {1, 2};    // This works because of a special rule
    static_assert(std::is_same<decltype(init_list), std::initializer_list<int>>::value, "not same");
    
    func(std::initializer_list<int>{1, 2});     // Ok. Has explicit type.
    
    func({1, 2});   // This doesn't because there's no rule for function
                    //      template parameter argument to deduce std::initializer_list
                    //      in this form.
}
