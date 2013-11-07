#include <ostream>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <stdexcept>
#include <cassert>

#include <iostream>
#include <string>

template<typename T, typename... Ts>
class packed_union
{
    public:
        template<typename V>
        typename std::enable_if<std::is_same<T, V>::value>::type operator=(V value)
        {
            uny.car = value;
        }
        
        template<typename V>
        typename std::enable_if<not std::is_same<T, V>::value>::type operator=(V value)
        {
            uny.cdr = value;
        }
    union
    {
        T car;
        packed_union<Ts...> cdr;
    } uny;
};

template<typename T>
class packed_union<T>
{
    public:
    template<typename V>
        typename std::enable_if<std::is_same<T, V>::value>::type operator=(V value)
        {
            uny.car = value;
        }
        /*
        template<typename V>
        typename std::enable_if<not std::is_same<T, V>::value>::type operator=(V value)
        {
            static_assert(not std::is_same<T, V>::value, "Invalid assigment");
        }
        */
        union
        {
            T car;
        } uny;
};

template<typename V, typename T, typename... Ts>
typename std::enable_if<std::is_same<T, V>::value, V>::type get_worker(packed_union<T, Ts...> packed_uny)
{
    return packed_uny.uny.car;
}

template<typename V, typename T, typename... Ts>
typename std::enable_if<not std::is_same<T, V>::value, V>::type get_worker(packed_union<T, Ts...> packed_uny)
{
    return get_worker<V>(packed_uny.uny.cdr);
}

template<typename T1, typename... Ts>
struct algebraic_datatype
{
    // TODO: Static_Assert no duplicates
    
    public:
        // TODO: Make default constructor, which default construct, an argument if any of the types has a default constructor
        
        template<typename T>
        algebraic_datatype(T value)
        : active_type(typeid(T))
        {
        }
    
        ~algebraic_datatype()
        {
        }
    
        template<typename T>
        void operator=(T value)
        {
            active_type = typeid(T);
            packed_uny = value;
        }
        
        template<typename T>
        T get_type()
        {
            if(std::type_index(typeid(T)) == active_type)
            {
                throw std::runtime_error("The requested type, is not the currently active one");
            }
            else
            {
                return get_worker<T>(packed_uny);
            }
        }
    public:
        std::type_index active_type;
        packed_union<T1, Ts...> packed_uny;
};

template<typename VISITOR, typename T>
typename VISITOR::return_type invoke_worker(VISITOR visitoz, std::type_index active_type,packed_union<T> packed_uny)
{
    assert(std::type_index(typeid(T)) == active_type); // "The active type was invalid"
    visitoz(packed_uny.uny.car);
}

template<typename VISITOR, typename T, typename... Ts>
typename VISITOR::return_type invoke_worker(VISITOR visitoz, std::type_index active_type, packed_union<T, Ts...> packed_uny)
{
    if(std::type_index(typeid(T)) == active_type)
    {
        visitoz(packed_uny.uny.car);
    }
    else
    {
        invoke_worker(visitoz, active_type, packed_uny.uny.cdr);
    }
}

template<typename VISITOR, typename T1, typename... Ts>
typename VISITOR::return_type invoke(VISITOR visitoz, algebraic_datatype<T1, Ts...> ad)
{
    invoke_worker(visitoz, ad.active_type, ad.packed_uny);
}

template<typename V, typename T1, typename... Ts>
V get(algebraic_datatype<T1, Ts...> ad)
{
    return get_worker<V>(ad.packed_uny);
}

struct op_ostream_help_visitor
{
    // TODO: Figure return_type from operator(),
    // by finding a common one (possibly just use the first operator()'s
    // return type, and assert inconsistency).
    using return_type = void;
    
    op_ostream_help_visitor(std::ostream& os)
    : os(os)
    {
    }
    
    std::ostream& os;
    
    template<typename T>
    return_type operator()(T t)
    {
        os << t;
    }
};

template<typename T1, typename... Ts>
std::ostream& operator<<(std::ostream& os, const algebraic_datatype<T1, Ts...>& ad)
{   
    op_ostream_help_visitor v(os);
    invoke(v, ad);   
    return os;
}

int main()
{
    algebraic_datatype<char, int, const char*> magic('C');
    
    magic = 'C';
    std::cout << get<char>(magic) << std::endl;
    std::cout << magic << std::endl;
    
    magic = 3;
    std::cout << get<int>(magic) << std::endl;
    std::cout << magic << std::endl;
    
    magic = "PO";
    std::cout << get<const char*>(magic) << std::endl;
    std::cout << magic << std::endl;
}