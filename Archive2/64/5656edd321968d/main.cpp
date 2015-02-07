 # include <iostream>

 enum any : int; // unscoped opaque declaration :int required by the standard

 enum : int  {a} t; // unscoped anonymous declaration of t (:int not required)

 enum any : int {b} u; // redlecaration of type "any" with one enumerator

 enum class foo : char; // scoped opaque declaration "foo" required, :char NOT

 enum class foo : char {a, b} Foo; // redeclaration of "foo" with 2 
                              // enumerators. now :char REQUIRED


 enum class : char {a} Enum; // scoped anonymous declaration of Enum
                        // wouldn't be disallowed?

int main()
  {
   t = a; // assignment to "t"
   u = b; // assignment to "u"
   Foo = foo::a; // assignment to "Foo"
   Enum = decltype(Enum)::d;  // allowed (??)
  std::cout << static_cast<int>(t) << ' '
  << static_cast<int>(u) << ' '
  << static_cast<int>(Foo) << ' '
  << static_cast<int>(Enum) << std::endl;
  }