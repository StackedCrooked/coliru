#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

template <typename T>
struct any_type {};

struct any {
public:
    
    template <typename T, typename ...Tn>
    any ( any_type<T>, Tn&&... argn ) : ti(nullptr), deleter(nullptr) {
        place<T>( std::forward<Tn>( argn )... );
    }
    
    ~any () {
        if ( ti != nullptr )
            destroy();
    }
    
    explicit operator bool () const {
        return can_get();
    } 
    
    template <typename T, typename ...Tn>
    void reset ( Tn&&... argn ) {
        if ( ti != nullptr )
            destroy();
        place<T>( std::forward<Tn>( argn )... );
    }
    
    bool can_get () const {
        return ti != nullptr;
    }
    
    template <typename T>
    bool can_get_as () const {
        if ( ti == nullptr || 
             typeid(T) != *ti )
             return false;
        return true;
    }

    template <typename T>
    T& get() {
        if ( ti == nullptr || 
             typeid(T) != *ti )
             throw std::runtime_error( "any: bast cast" );
        return *static_cast<T*>(static_cast<void*>(storage.data()));
    }
    
    template <typename T>
    const T& get() const {
        if ( ti == nullptr || 
             typeid(T) != *ti )
             throw std::runtime_error( "any: bast cast" );
        return *static_cast<T const*>(static_cast<void const*>(storage.data()));
    }

private:
    struct any_deleter {
        
        virtual void operator() ( any& a ) {
            
        }
    };

    template <typename T> 
    struct typed_deleter : public any_deleter {
        virtual void operator() ( any& a ) override {
            if ( a.ti == nullptr ||
                (*a.ti) != typeid( T ) )
                throw std::runtime_error( "any: Something horribly wrong happened" );
            
            std::cout << "Deleting memory of T" << std::endl;
            a.get<T>().~T();
        }
    };

    template <typename T, typename... Args>
    void place( Args&&... args ) {
        ti = &typeid( T );
        storage.resize( sizeof( T ) );
        deleter.reset( new typed_deleter<T>() );
        ::new( storage.data() ) T( std::forward<Args>(args)... );
    }
    
    void destroy () {
        (*deleter)( *this );
        deleter.reset( nullptr );
        ti = nullptr;
    }

    const std::type_info* ti;
    std::unique_ptr<any_deleter> deleter;
    std::vector<unsigned char> storage;
};

#include <iostream>

int main () {
    
    any od( any_type<double>(), 1.0 );
    std::cout << od.get<double>() << std::endl;
    od.reset<double>( 1.5 );
    std::cout << od.get<double>() << std::endl;
    std::cout << od.get<float>() << std::endl;
    
}