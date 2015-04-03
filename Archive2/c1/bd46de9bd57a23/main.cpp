#include <tuple>
#include <iostream>
#include <type_traits>

struct X {
   struct Y {
       int z;
   } y;
   int val;
};

// auto constexpr reflect = make_tuple( typedef<X> );

// expande para
#define TYPEDEF_X (X::Y*)nullptr, &X::y, &X::val
#define TYPEDEF_Y &X::Y::z

#define TYPENAME_X "X::Y", "y", "val"
#define TYPENAME_Y &X::Y::z

template<typename T>
struct member_type {
    typedef T type;
};

template<class Obj, typename Member>
struct member_type<Member Obj::*> {
    typedef Member type;
};

template<class Obj, typename Member>
struct member_type<Member (Obj::*)()> {
    typedef Member type;
};

template<typename T>
 struct is_class_or_enum {
    static constexpr bool value = std::is_class<T>::value || std::is_enum<T>::value;
};

template<typename T>
struct is_deep {
    static constexpr bool value = (std::is_member_object_pointer<T>::value   && is_class_or_enum<typename member_type<T>::type>::value ) ||
                                  (std::is_member_function_pointer<T>::value && is_class_or_enum<typename member_type<T>::type>::value ) ;
};

struct visitor {
    template<typename Obj, typename Name, typename Member>
    void operator()(Obj&, const Name&, const Member&) {}
};

struct deep_visit {
    template<typename Obj, typename Name, typename Member>
    static void visit(visitor& , Obj& , const Name& , const Member& ) {
    //   visit(v, x, typename<Obj>, typedef<Obj> ); 
    }
};

struct shallow_visit {
    template<typename Obj, typename Name, typename Member>
    static void visit(visitor&, Obj&, const Name&, const Member&) {
    }
};

template<typename Obj, typename Name, typename ...Names, typename Member, typename ...Members >
void visit(visitor& v, Obj& o, const Name& n, const Names&...ns, const Member& m, const Members&... ms) {
    v(o, n, m);
    std::conditional<is_deep<Member>::value, deep_visit, shallow_visit>::type::visit(v, o, n, m);
    visit(v, o, ns..., ms...);
}

template<typename Obj, typename Name, typename Member>
void visit(visitor& v, Obj& o, const Name& n, const Member& m) {
    v(o, m, n);
}

int main() {

   X x;
   x.val = 42;
   x.y.z = 43;
   
   visitor v;
   visit(v, x, TYPENAME_X, TYPEDEF_X );

   return 0;
}
