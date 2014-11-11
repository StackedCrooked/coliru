#include <iostream>
#include <string>
#include <type_traits>

template<class T>
struct RefOps {
    static constexpr bool specialized = false;
};

template<class Tag>
struct Ref {
    protected:
        void* something;
        void* another_thing;
        
    public:
        template<class T>
        typename std::conditional<RefOps<T>::specialized, RefOps<T>, Ref<T>>::type
        operator[](std::string name) {
           //magic->getMember(something, name.c_str); 
           return {};
        }
};

struct java {
    struct BeanProxyFactory {};
    struct lang {
        struct String{};
    };
};

template <>
class RefOps<java::lang::String> : Ref<java::lang::String> {
    public:
        static constexpr bool specialized = true;
        
        operator std::string() const {
            std::cout << something << ", " << another_thing << "\n";
            return "Testing everyone";
        }
};

int main() {
    auto some_instance = Ref<java::BeanProxyFactory>();
    
    std::string bean_string = some_instance.operator[]<java::lang::String>("createMagicBeanString");
    
    std::cout << bean_string << "\n";
}