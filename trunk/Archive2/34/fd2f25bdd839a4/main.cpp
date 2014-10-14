#include <iostream>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <utility>

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>{
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const> {
    static constexpr auto arity = sizeof...(Args);
    typedef ReturnType result_type;
    
    template <size_t i>
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    using args = std::tuple<Args...>;
};

template <class ReturnT>
struct DynamicFunctionDispatch {
    template <FT function>
    DynamicFunctionDispatch(FT f) {
    }
};

template <class ReturnT>
class OpenMultiMethod {
    private:
        std::unordered_map<std::vector<std::type_index>, DynamicFunctionDispatch<ReturnT>> methods;
        
        template<class FT, size_t... Is>
        void add_method(FT function, std::index_sequence<Is...>) {
            std::vector<std::type_index> args_t = { typeid(std::get<Is>)... };
            methods[args_t] = function;
        }
        
    public:
        template<class FT>
        void operator+=(FT function) {
            add_method(function, std::make_index_sequence<std::tuple_size<typename function_traits<FT>::args>::value>());
        }
    
        template<class... ArgsT>
        ReturnT operator()(ArgsT... args) {
            std::vector<std::type_index> args_t = { typeid(args)... };
        }
};

int main() {
}