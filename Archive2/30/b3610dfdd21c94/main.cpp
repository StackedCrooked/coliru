/// Disable copy construct/assign for the given class T
#define CLASS_NON_COPYABLE(T) \
   T(T const&) = delete; \
   T& operator=(T const&) = delete

/// Disable move construct/assign for the given class T
#define CLASS_NON_MOVABLE(T) \
   T(T&&) = delete; \
   T& operator=(T&&) = delete

/// Disable both copy and move construct/assign for the given class T
#define CLASS_NON_COPYABLE_OR_MOVABLE(T) \
   CLASS_NON_COPYABLE(T); \
   CLASS_NON_MOVABLE(T)

#define CLASS_DEFAULT_COPYABLE(T) \
   T(T const&) = default; \
   T& operator=(T const&) = default

#define CLASS_DEFAULT_MOVABLE(T) \
   T(T&&) = default; \
   T& operator=(T&&) = default

/// Defaulted versions of both copy and move construct/assign for the given class T
#define CLASS_DEFAULT_COPYABLE_OR_MOVABLE(T) \
   CLASS_DEFAULT_COPYABLE(T); \
   CLASS_DEFAULT_MOVABLE(T)



class foo
{
public:
    foo() = default;
    virtual ~foo() = default;
    
    CLASS_NON_COPYABLE(foo);
    CLASS_DEFAULT_MOVABLE(foo);
};

int main()
{
    foo a, b;
    a = b;
    
    a = foo();
}