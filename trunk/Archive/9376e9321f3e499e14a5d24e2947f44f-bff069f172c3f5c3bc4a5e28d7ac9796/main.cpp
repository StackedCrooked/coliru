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

/* Memeory check:

==31767== Memcheck, a memory error detector
==31767== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==31767== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==31767== Command: ./test
==31767== 
Proper: 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
Garbage: 
Construct by nothing
==31767== Conditional jump or move depends on uninitialised value(s)
==31767==    at 0x4EC4F16: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC514C: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC8015: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x400ECF: main (test.cpp:84)
==31767== 
==31767== Use of uninitialised value of size 8
==31767==    at 0x4EBA343: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC4F37: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC514C: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC8015: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x400ECF: main (test.cpp:84)
==31767== 
==31767== Conditional jump or move depends on uninitialised value(s)
==31767==    at 0x4EBA34F: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC4F37: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC514C: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC8015: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x400ECF: main (test.cpp:84)
==31767== 
==31767== Conditional jump or move depends on uninitialised value(s)
==31767==    at 0x4EC4F66: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC514C: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x4EC8015: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17)
==31767==    by 0x400ECF: main (test.cpp:84)
==31767== 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ==31767== 
==31767== HEAP SUMMARY:
==31767==     in use at exit: 0 bytes in 0 blocks
==31767==   total heap usage: 2 allocs, 2 frees, 400 bytes allocated
==31767== 
==31767== All heap blocks were freed -- no leaks are possible
==31767== 
==31767== For counts of detected and suppressed errors, rerun with: -v
==31767== Use --track-origins=yes to see where uninitialised values come from
==31767== ERROR SUMMARY: 200 errors from 4 contexts (suppressed: 2 from 2)

*/