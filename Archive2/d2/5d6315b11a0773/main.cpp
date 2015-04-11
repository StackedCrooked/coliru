#include <type_traits>
#include <cstddef>

typedef int lua_State;
typedef int (*lua_Writer) (lua_State *L,
                           const void* p,
                           size_t sz,
                           void* ud);

namespace sol { namespace stack {
    namespace detail {
        template <typename T>
        struct generic_writer {
            T fx;
            void* callback_data;
        };
        
        template <typename T>
        static int generic_write (lua_State *L,
                           const void* p,
                           size_t sz,
                           void* ud) {
            generic_writer<T>* pwriter = static_cast<generic_writer<T>*>( ud );
            generic_writer<T>& writer = *pwriter;
            return writer.fx( L, p, sz, writer.callback_data );
        }
    }
    
    // http://www.lua.org/manual/5.3/manual.html#lua_dump
    int dump (lua_State *L, lua_Writer writer, void* data, int strip) {
        // make-up core implementation for lua_dump
        int someint = 24;
        return writer( L, &someint, sizeof( someint ), data );
    }
    
    template <typename T>
    int dump (lua_State *L, T&& fx, void* data = nullptr, int strip = 0) {
        auto writer = detail::generic_writer<T>{ fx, data }; 
        return dump(L, &detail::generic_write<T>, &writer, strip);
    }
}}

#include <iostream>

struct my_writer {
    int operator() (lua_State *L, const void* p, size_t sz, void* ud) {
        std::cout << "Got pointer " << p << "with a derefernced size of " << sz << " and with callback data " << ud << ".\n"; 
        return 0;
    }
};

int main() {
    int some_callback_data = 0;
    lua_State* L = 0; // pretend initialzation
    sol::stack::dump( L, my_writer{}, &some_callback_data ); 
    
}