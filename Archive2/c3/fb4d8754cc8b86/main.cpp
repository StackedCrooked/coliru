#include <iostream>
#include <type_traits>
#include <typeindex>
#include <map>
#include <vector>
#include <tuple>
#include <utility>
#include <functional>
#include <memory>
#include <stdexcept>
#include <boost/any.hpp>

#include <string>

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
class DynamicFunction {
    private:
        template<class... ArgsT, size_t... Is>
        ReturnT op_call_helper(std::index_sequence<Is...> arg_indices, ArgsT&&... args) {
            auto arg_storage = std::make_tuple(args...);
            return call({std::get<Is>(arg_storage)...});
        }
        
    protected:
        virtual ReturnT call(std::vector<boost::any> args) = 0;
        
    public:
        template <class... ArgsT>
        ReturnT operator()(ArgsT&&... args) {
            return op_call_helper(std::index_sequence_for<ArgsT...>(), args...);
        }
};

template <class FT>
class DynamicFunctionImpl : public DynamicFunction<typename function_traits<FT>::result_type> {
    private:
        using ReturnT = typename function_traits<FT>::result_type;
        FT f_storage;

        template<class... ArgsT, size_t... Is>
        ReturnT call_helper(std::vector<boost::any> args, std::index_sequence<Is...> indices) {
            auto argument_transport = std::make_tuple(boost::any_cast<typename std::tuple_element<Is, typename function_traits<FT>::args>::type>(args[Is])...);
            return f_storage(std::get<Is>(argument_transport)...);
        }
        
    protected:
        virtual ReturnT call(std::vector<boost::any> args) {
            return call_helper(args, std::make_index_sequence<std::tuple_size<typename function_traits<FT>::args>::value>());
        }
        
    public:
        DynamicFunctionImpl(FT f) : f_storage(f) {
        }
};

using runtime_signature = std::vector<std::type_index>;

template <class ReturnT>
class OpenMultiMethod {
    private:
        std::map<runtime_signature, std::unique_ptr<DynamicFunction<ReturnT>>> methods;
        
        template<class FT, size_t... Is>
        void add_method(FT function, std::index_sequence<Is...>) {
            runtime_signature args_t = { typeid(typename std::tuple_element<Is, typename function_traits<FT>::args>::type)... };
            methods[args_t] = std::unique_ptr<DynamicFunction<ReturnT>>(new DynamicFunctionImpl<FT>(function));
        }
        
    public:
        template<class FT>
        void operator+=(FT function) {
            add_method(function, std::make_index_sequence<std::tuple_size<typename function_traits<FT>::args>::value>());
        }
    
        template<class... ArgsT>
        ReturnT operator()(ArgsT... args) {
            runtime_signature signature = { typeid(args)... };
            if(methods.find(signature) == methods.end()) {
                throw std::runtime_error("Could not match dynamic signature");
            } else {
                return (*methods[signature])(args...);
            }
        }
};

using namespace std::string_literals;

int main() {
    OpenMultiMethod<void> foo;
    foo += [](double a, double b) { std::cout << a << ", " << b << "\n";};
    foo += [](int a, double b, std::string another_thing) { std::cout << a << ", " << b << another_thing  << "\n";};
    foo(1.0, 2.0);
    foo(300, 6.9, "hi gaylord"s);
    foo("wanker");
}