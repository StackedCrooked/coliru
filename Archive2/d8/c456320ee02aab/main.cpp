struct S {};
typedef struct S T;
S s = T();          // OK
struct T * p;       // error: elaborated type refers to a typedef
T{};                // error: expected unqualified-id
T::T(){}            // error: C++ requires a type specifier for all declarations