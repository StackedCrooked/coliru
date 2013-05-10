#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>

template <typename T>
struct identity_type {
    typedef T type;
};

template <typename T>
struct allocator_deleter {
    T& allocator;
    
    allocator_deleter ( T& alloc ) : allocator( alloc ) {
        
    }
    
    void operator () ( typename T::pointer pointer ) {
        allocator.destroy( pointer );
        allocator.deallocate( pointer, 1 );
    }
    
};

struct any {
private:
    struct any_storage {
        
        virtual void* data () {
            return nullptr;
        }
        
        virtual ~any_storage () {
            
        }
    };

    template <typename T> 
    struct typed_storage : public any_storage {
        T item;
        
        template <typename ...Tn>
        typed_storage ( Tn&&... argn ) : item(std::forward<Tn>( argn )...) {
        
        }
        
        virtual void* data () override {
            return static_cast<void*>( &item );
        }
        
    };

    template <typename T, typename TAlloc = std::allocator<T>> 
    struct typed_allocated_storage : public any_storage {
        TAlloc allocator;
        std::unique_ptr<T, allocator_deleter<TAlloc>> item;
        
        template <typename ...Tn>
        typed_allocated_storage ( Tn&&... argn ) : allocator(TAlloc()), item(allocator.allocate(1), allocator ) {
            allocator.construct( item.get(), std::forward<Tn>( argn )... );
        }
        
        template <typename ...Tn>
        typed_allocated_storage ( TAlloc&& alloc, Tn&&... argn ) : allocator(std::move(alloc)), item(allocator.allocate(1), allocator )  {
            item = allocator.allocate( 1 );
            allocator.construct( item, std::forward<Tn>( argn )... );
        }
        
        virtual void* data () override {
            return static_cast<void*>( item );
        }
        
        ~typed_allocated_storage () {
            
        }
        
    };
    
public:
    
    template <typename T>
    any ( T&& mov ) : ti(nullptr), storage(nullptr) {
        place<T>( std::move( mov ) );
    }
    
    template <typename T>
    any ( const T& copy ) : ti(nullptr), storage(nullptr) {
        place<T>( copy );
    }
    
    template <typename T, typename ...Tn>
    any ( identity_type<T>, Tn&&... argn ) : ti(nullptr), storage(nullptr) {
        place<T>( std::forward<Tn>( argn )... );
    }
    
    template <typename T, typename TAlloc, typename ...Tn>
    any ( identity_type<T>, std::allocator_arg_t allocarg, TAlloc&& alloc, Tn&&... argn ) : ti(nullptr), storage(nullptr) {
        place<T, TAlloc>( allocarg, std::forward<TAlloc>( alloc ), std::forward<Tn>( argn )... );
    }
    
    any ( any&& mov ) : ti(mov.ti), storage(std::move(mov.storage)) {
        mov.storage.release();
        mov.storage.reset( nullptr );
        mov.ti = nullptr;
    }
    
    any& operator= ( any&& mov ) {
        storage = std::move( mov.storage );
        ti = mov.ti;
        mov.storage.release();
        mov.storage.reset( nullptr );
        mov.ti = nullptr;
        return *this;
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
    
    template <typename T, typename TAlloc, typename ...Tn>
    void reset ( std::allocator_arg_t allocarg, TAlloc&& alloc, Tn&&... argn ) {
        if ( ti != nullptr )
            destroy();
        place<T, TAlloc>( allocarg, std::forward<TAlloc>( alloc ), std::forward<Tn>( argn )... );
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
        if ( !can_get_as<T>() )
             throw std::runtime_error( "any: bast cast" );
        return *static_cast<T*>( storage->data() );
    }
    
    template <typename T>
    const T& get() const {
        if ( !can_get_as<T>() )
             throw std::runtime_error( "any: bast cast" );
        return *static_cast<T const*>( storage->data() );
    }

private:
    
    void destroy () {
        storage.reset( nullptr );
        ti = nullptr;
    }

    template <typename T, typename... Tn>
    void place( Tn&&... argn ) {
        ti = &typeid( T );
        storage.reset( new typed_storage<T>( std::forward<Tn>(argn)... ) );
    }

    template <typename T, typename TAlloc, typename... Tn>
    void place( std::allocator_arg_t allocarg, TAlloc&& alloc, Tn&&... argn ) {
        ti = &typeid( T );
        storage.reset( new typed_allocated_storage<T, TAlloc>( std::forward<TAlloc>( alloc ), std::forward<Tn>(argn)... ) );
    }

    const std::type_info* ti;
    std::unique_ptr<any_storage> storage;
};

#include <iostream>

int main () {
    
    any od( identity_type<double>(), 1.0 );
    std::cout << od.get<double>() << std::endl;
    od.reset<double>( 1.5 );
    std::cout << od.get<double>() << std::endl;
    std::cout << od.get<float>() << std::endl;
    
}