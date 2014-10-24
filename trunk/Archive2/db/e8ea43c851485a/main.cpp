#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <functional>
#include <memory>
#include <stdexcept>

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>{
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const> {
    static constexpr auto arity = sizeof...(Args);
    typedef ReturnType result_type;
    
    template <size_t i>
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
};


template<class T>
struct ArgumentWrapped {
    using type = T*;
};

template<class T>
struct ArgumentWrapped<T&> {
    using type = std::reference_wrapper<T>;
};

template<class T>
T* unwrap_argument(T**& arg) {
    return *arg;
}

template<class T>
T& unwrap_argument(std::reference_wrapper<T>& arg) {
    return arg.get();
}

using argument_storage = const std::vector<void*>;

template <class ReturnT>
class DynamicFunction {
    private:
        template<class... ArgsT, size_t...Is>
        ReturnT call_helper(std::index_sequence<Is...>, ArgsT&&... args) {
            auto typesafe_arguments = std::tuple<typename ArgumentWrapped<ArgsT>::type...>(args...);
            argument_storage erased_arguments = { &std::get<Is>(typesafe_arguments)... };
            return call(erased_arguments);
        }

    protected:
        virtual ReturnT call(argument_storage args) = 0;
        
    public:
        template <class... ArgsT>
        ReturnT operator()(ArgsT&&... args) {
            return call_helper(std::make_index_sequence<sizeof...(ArgsT)>(), std::forward<ArgsT>(args)...);
        }

};

template <class FT>
class DynamicFunctionImpl : public DynamicFunction<typename function_traits<FT>::result_type> {
    private:
        using ReturnT = typename function_traits<FT>::result_type;
        static const constexpr auto Arity = function_traits<FT>::arity;
        FT f_storage;

        template<size_t... Is>
        ReturnT call_helper(argument_storage erased_arguments, std::index_sequence<Is...> indices) {
            auto typesafe_arguments = std::make_tuple(reinterpret_cast<typename ArgumentWrapped<typename function_traits<FT>::template arg<Is>>::type*>(erased_arguments[Is])...);
            return f_storage(unwrap_argument(*(std::get<Is>(typesafe_arguments)))...);
        }
        
    protected:
        virtual ReturnT call(argument_storage args) {
            return call_helper(args, std::make_index_sequence<Arity>());
        }
        
    public:
        DynamicFunctionImpl(FT f) : f_storage(f) {
        }
};

using runtime_signature = std::vector<std::type_index>;

namespace std {
    template<>
    struct hash<runtime_signature> {
        size_t operator()(const runtime_signature& x) const {
            size_t seed = 0;
            std::hash<std::type_index> hasher;
            for(auto const& type_index : x) {
                seed ^= hasher(type_index) + 0x9e3779b9 + (seed << 6) + (seed >> 2); // see http://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
            }
            return seed;
        }
    };
}

template <class ReturnT>
class OpenMultiMethod {
    public:
        using FPtr = typename std::unique_ptr<DynamicFunction<ReturnT>>;

        std::unordered_map<runtime_signature, FPtr> overloads;

        template<class FT, size_t... Is>
        void add_method(FT function, std::index_sequence<Is...>) {
            runtime_signature sig = { typeid(typename function_traits<FT>::template arg<Is>)... };
            overloads[sig] = std::make_unique<DynamicFunctionImpl<FT>>(function);
        }

        template<class... ArgsT>
        DynamicFunction<ReturnT>* resolve_overload(ArgsT&&... args) {
            return overloads[{ typeid(args)... }].get();
        }
        
    public:
        template<class FT>
        void operator+=(FT function) {
            add_method(function, std::make_index_sequence<function_traits<FT>::arity>());
        }
    
        template<class... ArgsT>
        ReturnT operator()(ArgsT&&... args) {
            auto overload = overloads.find({ typeid(args)...});
            if(overload == overloads.end()) {
                throw std::runtime_error("No matching signature found");
            } else {
                DynamicFunction<ReturnT>* f = overload->second.get();
                return (*f)(args...);
            }
        }
};

class Parent {
    virtual void make_vtable() {}
};
struct ChildA : Parent {};
struct ChildB : Parent {};
struct NoChildOfMine {};


int main() {
    OpenMultiMethod<int> colliding;
    colliding += [](ChildA& a, ChildB& b) { std::cout << "AB\n"; return 100;};
    colliding += [](ChildA& a, ChildA& b) { std::cout << "AA\n"; return 100;};
    colliding += [](Parent* a, ChildA& b) { std::cout << "P*A\n"; return 100;};
    
    Parent* a = new ChildA();
    Parent* b = new ChildB();
    ChildA* ca = static_cast<ChildA*>(a);
    ChildB* cb = static_cast<ChildB*>(b);
    
    std::cout << colliding(*a, *b);
    colliding(*a, *a);
    colliding(a, *a);
}