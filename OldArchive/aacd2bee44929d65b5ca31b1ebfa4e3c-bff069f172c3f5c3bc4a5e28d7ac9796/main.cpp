#include <type_traits>
#include <utility>
#include <vector>
#include <iostream>

template <typename T>
class uninitialized_allocator
{
public:
    typedef T value_type;

    uninitialized_allocator() {
    
    }
    
    // All uninitialized_allocators behave the same way; should be copiable all
    // around the block
    template <typename U>
    uninitialized_allocator(const uninitialized_allocator<U>&) {
        
    }
    
    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    
    void deallocate(T* p, std::size_t) noexcept {
        // using void* rejects possiblity of calling
        // the destructor either for T.
        // Relationship is symmetric: trivially constructible must also be trivially destructible
        ::operator delete(static_cast<void*>(p));
    }
    
    // Is this extra level or templating truly necessary
    // On this function and the next... ?
    // Maybe. It is no-init, so all no-inits should work with it exactly as-is, I suppose
    // (Less strict than usual?)
    template <typename TPtr>
    void construct( TPtr* ) {
        // It must be trivially constructible/destructible -- so assert when `T` is not
        // GCC doesn't have default_constructible type_trait. Lovely.
        //static_assert(std::is_trivially_default_constructible<TPtr>::value, "This allocator can only be used with trivally default constructible types");
        // This one should be enough of a guarantee, really
        static bool sayit = false;
        if ( !sayit ) {
            std::cout << "Construct by nothing" << std::endl;
            sayit = true;
        }
        static_assert(std::is_trivially_destructible<TPtr>::value, "This allocator can only be used with trivally default destrcutible types");
    }
    
    
    template <typename TPtr, typename T0, typename... Tn>
    void construct(TPtr* ptr, T0&& arg0, Tn&&... argn) {
        // If we have to construct from args, then do so regularly with placement new
        static bool sayit = false;
        if ( !sayit ) {
            std::cout << "Construct by value" << std::endl;
            sayit = true;
        }
        ::new(ptr) TPtr(std::forward<T0>(arg0), std::forward<Tn>(argn)...);
    }
};

int main() {
    std::cout << "Proper: " << std::endl;
    std::vector<int> proper( 50 );
    for ( unsigned g = 50; g--; ) {
        std::cout << proper[g] << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Garbage: " << std::endl;
    std::vector<int, uninitialized_allocator<int>> garbage( 50 );
    for ( unsigned g = 50; g--; ) {
        std::cout << garbage[g] << ", ";
    }
}