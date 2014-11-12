#include <iostream>
#include <string>
#include <stdexcept>
#include <map>
#include <typeindex>

template<typename T>
    class TypeMap {
        T value;
        std::map<std::type_index, TypeMap<T>> children;
    public:
        TypeMap() = default;
        template<typename T1>
        void insert(T&& value) {
            children[typeid(T1)] = TypeMap<T>();
            children[typeid(T1)].value = value;
        }
        template<typename T1, typename T2, typename... Tn>
        void insert(T&& value) {
            children[typeid(T1)] = TypeMap<T>();
            children[typeid(T1)].template insert<T2, Tn...>(std::move(value));
        }
        
        template<typename T1>
        T& get() {
            if(children.count(typeid(T1)) > 0) return children.at(typeid(T1)).value;
            else throw std::invalid_argument("");
        }
        template<typename T1, typename T2, typename... Tn>
        T& get() {
            if(children.count(typeid(T1)) > 0) return children.at(typeid(T1)).template get<T2, Tn...>();
            else throw std::invalid_argument("");
        }
    };


int main()
{
    TypeMap<std::string> tm;
    tm.insert<int, double, bool>("Hey");
    auto st = tm.get<int, double, bool>();
    std::cout << st << std::endl;
}
