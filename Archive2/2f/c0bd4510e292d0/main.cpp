#include <iostream>
#include <type_traits>
#include <memory>
#include <tuple>
#include <utility>
#include <typeindex>

template<class MyT>
struct identity {
    using T = MyT;
};

class QualifiedTypeID {
    private:
        bool is_const;
        bool is_volatile;
        bool is_lvalue_ref;
        bool is_rvalue_ref;
        std::type_index type_index;
    public:
        template<class T>
        QualifiedTypeID(identity<T>) :
            is_const(std::is_const<T>::value),
            is_volatile(std::is_volatile<T>::value),
            is_lvalue_ref(std::is_lvalue_reference<T>::value),
            is_rvalue_ref(std::is_rvalue_reference<T>::value),
            type_index(typeid(T))
             {
        }
        void summarize() {
            if(is_const) {
                std::cout << "const ";
            }
            if(is_volatile) {
                std::cout << "volatile ";
            }
            std::cout << type_index.name();
            if(is_lvalue_ref) {
                std::cout << "&";
            }
            if(is_rvalue_ref) {
                std::cout << "&&";
            }
            std::cout << "\n";
        }
};

template<class T>
void summarize_value(T&&) {
    QualifiedTypeID(identity<T&&>()).summarize();
};

int main() {
    int i;
    summarize_value(100);
    summarize_value(i);
}