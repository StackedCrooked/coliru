// The following headers are required for all allocators.
#include <stddef.h>  // Required for size_t and ptrdiff_t and NULL
#include <new>       // Required for placement new and std::bad_alloc
#include <stdexcept> // Required for std::length_error
 
// The following headers contain stuff that Mallocator uses.
#include <stdlib.h>  // For malloc() and free()
#include <iostream>  // For std::cout
#include <ostream>   // For std::endl
 
// The following headers contain stuff that main() uses.
#include <list>      // For std::list
 
template <typename T> class Mallocator {
public:
 
    // The following will be the same for virtually all allocators.
    typedef T * pointer;
    typedef const T * const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
 
    T * address(T& r) const {
        return &r;
    }
 
    const T * address(const T& s) const {
        return &s;
    }
 
    size_t max_size() const {
        // The following has been carefully written to be independent of
        // the definition of size_t and to avoid signed/unsigned warnings.
        return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T);
    }
 
 
    // The following must be the same for all allocators.
    template <typename U> struct rebind {
        typedef Mallocator<U> other;
    };
 
    bool operator!=(const Mallocator& other) const {
        return !(*this == other);
    }
 
    void construct(T * const p, const T& t) const {
        void * const pv = static_cast<void *>(p);
 
        new (pv) T(t);
    }
 
    void destroy(T * const p) const; // Defined below.
 
 
    // Returns true if and only if storage allocated from *this
    // can be deallocated from other, and vice versa.
    // Always returns true for stateless allocators.
    bool operator==(const Mallocator& other) const {
        return true;
    }
 
 
    // Default constructor, copy constructor, rebinding constructor, and destructor.
    // Empty for stateless allocators.
    Mallocator() { }
 
    Mallocator(const Mallocator&) { }
 
    template <typename U> Mallocator(const Mallocator<U>&) { }
 
    ~Mallocator() { }
 
 
    // The following will be different for each allocator.
    T * allocate(const size_t n) const {
        // Mallocator prints a diagnostic message to demonstrate
        // what it's doing. Real allocators won't do this.
        std::cout << "Allocating " << n << (n == 1 ? " object" : "objects")
            << " of size " << sizeof(T) << "." << std::endl;
 
        // The return value of allocate(0) is unspecified.
        // Mallocator returns NULL in order to avoid depending
        // on malloc(0)'s implementation-defined behavior
        // (the implementation can define malloc(0) to return NULL,
        // in which case the bad_alloc check below would fire).
        // All allocators can return NULL in this case.
        if (n == 0) {
            return NULL;
        }
 
        // All allocators should contain an integer overflow check.
        // The Standardization Committee recommends that std::length_error
        // be thrown in the case of integer overflow.
        if (n > max_size()) {
            throw std::length_error("Mallocator<T>::allocate() - Integer overflow.");
        }
 
        // Mallocator wraps malloc().
        void * const pv = malloc(n * sizeof(T));
 
        // Allocators should throw std::bad_alloc in the case of memory allocation failure.
        if (pv == NULL) {
            throw std::bad_alloc();
        }
 
        return static_cast<T *>(pv);
    }
 
    void deallocate(T * const p, const size_t n) const {
        // Mallocator prints a diagnostic message to demonstrate
        // what it's doing. Real allocators won't do this.
        std::cout << "Deallocating " << n << (n == 1 ? " object" : "objects")
            << " of size " << sizeof(T) << "." << std::endl;
 
        // Mallocator wraps free().
        free(p);
    }
 
 
    // The following will be the same for all allocators that ignore hints.
    template <typename U> T * allocate(const size_t n, const U * /* const hint */) const {
        return allocate(n);
    }
 
 
    // Allocators are not required to be assignable, so
    // all allocators should have a private unimplemented
    // assignment operator. Note that this will trigger the
    // off-by-default (enabled under /Wall) warning C4626
    // "assignment operator could not be generated because a
    // base class assignment operator is inaccessible" within
    // the STL headers, but that warning is useless.
private:
    Mallocator& operator=(const Mallocator&);
};
 
// A compiler bug causes it to believe that p->~T() doesn't reference p.
 
#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4100) // unreferenced formal parameter
#endif
 
// The definition of destroy() must be the same for all allocators.
template <typename T> void Mallocator<T>::destroy(T * const p) const {
    p->~T();
}
 
#ifdef _MSC_VER
    #pragma warning(pop)
#endif
 
 
int main() {
    using namespace std;
 
    cout << "Constructing l:" << endl;
 
    list<int, Mallocator<int> > l;
 
    cout << endl << "l.push_back(1729):" << endl;
 
    l.push_back(1729);
 
    cout << endl << "l.push_back(2161):" << endl;
 
    l.push_back(2161);
 
    cout << endl;
 
    for (list<int, Mallocator<int> >::const_iterator i = l.begin(); i != l.end(); ++i) {
        cout << "Element: " << *i << endl;
    }
 
    cout << endl << "Destroying l:" << endl;
}