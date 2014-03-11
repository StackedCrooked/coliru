class C {
    std::string member; // decl-specifier-seq is "std::string"
                        // declarator is "member"
} obj, *pObj(&obj);
// decl-specifier-seq is "class C { std::string member; }"
// declarator "obj" defines an object of type C
// declarator "*pObj(&obj)" declares and initializes a pointer to C
 
int a = 1, *p = NULL, f(), (*pf)(double);
// decl-specifier-seq is int
// declarator a=1 defines and initializes a variable of type int
// declarator *p=NULL defines and initializes a variable of type int*
// declarator (f)() declares (but doesn't define)
//                  a function taking no arguments and returning int
// declarator (*pf)(double) defines a pointer to function
//                  taking double and returning int
 
int (*(*foo)(double))[3] = NULL;
// decl-specifier-seq is int
// 1. declarator "(*(*foo)(double))[3]" is an array declarator:
//    the type declared is "/nested declarator/ array of 3 int"
// 2. the nested declarator is "*(*foo)(double))", which is a pointer declarator
//    the type declared is "/nested declarator/ pointer to array of 3 int"
// 3. the nested declarator is "(*foo)(double)", which is a function declarator
//    the type declared is "/nested declarator/ function taking double and returning
//        pointer to array of 3 int"
// 4. the nested declarator is "(*foo)" which is a (parenthesized, as required by
//        function declarator syntax) pointer declarator.
//    the type declared is "/nested declarator/ pointer to function taking double
//        and returning pointer to array of 3 int"
// 5. the nested declarator is "foo", which is an identifier.
// The declaration declares the object foo of type "pointer to function taking double 
//     and returning pointer to array of 3 int"
// The initializer "= NULL" provides the initial value of this pointer.