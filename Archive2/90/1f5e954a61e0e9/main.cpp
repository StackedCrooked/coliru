#include <iostream>
#include <type_traits>
#include <cstring>

template <typename TFx, typename T, typename... Args>
auto call_member_fn ( T& object, Args&&... args )
-> decltype( (object.*(TFx()))( std::forward<Args>( args )... ) ){
     TFx p = TFx();
     return (object.*p)( std::forward<Args>( args )... );
}
 
struct A {
    int arf () {
        std::cout << "I WANNA BE, THE VERY BEST. LIKE NO ONE EVER WAS!" << std::endl;
        return 2;
    }
};

typedef unsigned char byte;
typedef decltype( &A::arf ) arf_t;
typedef byte( storage_t )[ sizeof( arf_t ) ];
    
 
void da_call ( const storage_t& work_the_system ) {
    A a;
    arf_t arfcall;
    std::memcpy( std::addressof( arfcall ), std::addressof( work_the_system ), sizeof( arf_t ) );
    std::cout << (a.*arfcall)( ) << std::endl;
}
 
int main() {
    auto da_func = &A::arf;
    storage_t da_bytes = { };
    std::memcpy( std::addressof( da_bytes ), std::addressof( da_func ), sizeof( &A::arf ) );
    // PRETEND LOTS OF TIME PASSES, STORAGE HAPPENS, BLAH BLAH BLAH
    da_call( da_bytes );
    
}