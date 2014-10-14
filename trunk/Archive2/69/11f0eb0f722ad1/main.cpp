#include <iostream>
#include <type_traits>
#include <typeindex>
#include <map>
#include <vector>
#include <tuple>
#include <utility>
#include <functional>
#include <memory>

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
class DynamicFunctionDispatch {
    private:
        template<class... ArgsT, size_t... Is>
        ReturnT op_call_helper(std::index_sequence<Is...> arg_indices, ArgsT... args) {
            auto arg_storage = std::make_tuple(args...);
            //return call({ std::make_pair(typeid(args), &std::get<arg_indices>(arg_storage))...});
            return call({&std::get<Is>(arg_storage)...});
        }
        
    protected:
        virtual ReturnT call(std::vector<void*> args) = 0;
        
    public:
        template <class... ArgsT>
        ReturnT operator()(ArgsT... args) {
            return op_call_helper(std::index_sequence_for<ArgsT...>(), args...);
        }
};

template <class FT>
class Foo : public DynamicFunctionDispatch<typename function_traits<FT>::result_type> {
    private:
        using ReturnT = typename function_traits<FT>::result_type;
        FT f_storage;

        template<class... ArgsT, size_t... Is>
        ReturnT call_helper(std::vector<void*> args, std::index_sequence<Is...> indices) {
            auto argument_transport = std::make_tuple(reinterpret_cast<typename std::tuple_element<Is, typename function_traits<FT>::args>::type*>(args[Is])...);
            return f_storage(*std::get<Is>(argument_transport)...);
        }
        
    protected:
        virtual ReturnT call(std::vector<void*> args) {
            return call_helper(args, std::make_index_sequence<std::tuple_size<typename function_traits<FT>::args>::value>());
        }
        
    public:
        Foo(FT f) : f_storage(f) {
        }
};


template <class ReturnT>
class OpenMultiMethod {
    private:
        std::map<std::vector<std::type_index>, std::unique_ptr<DynamicFunctionDispatch<ReturnT>>> methods;
        
        template<class FT, size_t... Is>
        void add_method(FT function, std::index_sequence<Is...>) {
            std::vector<std::type_index> args_t = { typeid(std::tuple_element<Is, typename function_traits<FT>::args>)... };
            methods[args_t] = std::unique_ptr<DynamicFunctionDispatch<ReturnT>>(new Foo<FT>(function));
        }
        
    public:
        template<class FT>
        void operator+=(FT function) {
            add_method(function, std::make_index_sequence<std::tuple_size<typename function_traits<FT>::args>::value>());
        }
    
        template<class... ArgsT>
        ReturnT operator()(ArgsT... args) {
            std::vector<std::type_index> args_t = { typeid(args)... };
            return (*methods[args_t])(args...);
        }
};

int main() {
    OpenMultiMethod<bool> colliding;
    colliding += [](int a, double b) { return true; };
    std::cout << colliding(1, 2.0) << "\n";
}