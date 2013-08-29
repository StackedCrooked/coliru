#include <future>
#include <iostream>
#include <boost/variant.hpp>
#include <memory>
#include <vector>

// metaprogramming boilerplate:

// sequences of offsets:
template<std::size_t...>
struct seq {};
template<std::size_t Min, std::size_t Max, std::size_t... s>
struct make_seq:make_seq<Min, Max-1, Max-1, s...> {};
template<std::size_t Min, std::size_t... s>
struct make_seq<Min, Min, s...> {
    typedef seq<Min, s...> type;
};
template<std::size_t Max, std::size_t Min=0>
using MakeSeq = typename make_seq<Min, Max>::type;

// utility function to do a sequence of tasks in a particular order:
void do_in_order() {}
template<typename F0, typename... Fs>
void do_in_order( F0&& f0, Fs&&... fs ) {
    std::forward<F0>(f0)();
    do_in_order( std::forward<Fs>(fs)... );
}

// Enable If helper:
template<std::size_t>
struct secret_enum { enum class type {}; };
template<std::size_t n>
using SecretEnum = typename secret_enum<n>::type;

template<bool b, std::size_t n = 0>
using EnableIf = typename std::enable_if< b, SecretEnum<n> >::type;

// stores a bundle of types:
template<typename...>
struct type_list {};

// Copies types from one template<typename...> to another:
template<typename L, template<typename...>class Targ>
struct copy_types;
template<template<typename...>class L, typename... Ts, template<typename...>class Targ>
struct copy_types< L<Ts...>, Targ > {
    typedef Targ<Ts...> type;
};
template<typename L, template<typename...>class Targ>
using CopyTypes = typename copy_types<L, Targ>::type;

template<typename T, typename=void>
struct do_clone {
    template<typename U>
    T* operator()( U&& u ) const {
        return std::forward<U>(u)->clone();
    }
};
#define RETURNS(X) ->decltype(X) { return (X); }
template<typename T>
struct value_ptr;
template<typename T> struct is_value_ptr: std::false_type {};
template<typename T> struct is_value_ptr< value_ptr<T> >: std::true_type {};
template<typename T> struct is_value_ptr< value_ptr<T>& >: std::true_type {};
template<typename T> struct is_value_ptr< value_ptr<T>const& >: std::true_type {};
template<typename T> struct is_value_ptr< value_ptr<T>&& >: std::true_type {};

template<typename T>
struct value_ptr {
    std::unique_ptr<T> val;

    explicit value_ptr( T* ptr ):val(ptr) {};
    explicit value_ptr( std::nullptr_t ):val() {};
    explicit value_ptr():val() {};
    
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr( value_ptr<U>&& o ): val(std::move(o.val)) {}
    value_ptr( value_ptr<T>&& o ): val(std::move(o.val)) {}
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr( value_ptr<U> const& o ): val(o.val?do_clone<U>()(o.val.get()):nullptr) {}
    value_ptr( value_ptr<T> const& o ): val(o.val?do_clone<T>()(o.val.get()):nullptr) {}
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr( value_ptr<U>& o ): val(o.val?do_clone<U>()(o.val.get()):nullptr) {}
    value_ptr( value_ptr<T>& o ): val(o.val?do_clone<T>()(o.val.get()):nullptr) {}
    
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr<T>& operator=( value_ptr<U>&& o ) {
        val = std::move(o.val);
        return *this;
    }
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr<T>& operator=( value_ptr<U> const& o ) {
        val = (o.val?do_clone<U>()(o.val.get()):nullptr);
        return *this;
    }
    template<typename U, typename=typename std::enable_if< std::is_base_of< T, U >::value>::type>
    value_ptr<T>& operator=( value_ptr<U>& o ) {
        val = (o.val?do_clone<U>()(o.val.get()):nullptr);
        return *this;
    }
    
    ~value_ptr() {}
    
    T* operator->() { return val.operator->(); }
    T const* operator->() const { return val.operator->(); }
    T& operator*() { return val.operator*(); }
    T const& operator*() const { return val.operator*(); }
    T* get() { return val.get(); }
    T const* get() const { return val.get(); }
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator==(RHS&& rhs) const RETURNS ( val == std::forward<RHS>(rhs) );
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator!=(RHS&& rhs) const RETURNS ( val != std::forward<RHS>(rhs) );
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator<=(RHS&& rhs) const RETURNS ( val <= std::forward<RHS>(rhs) );
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator>=(RHS&& rhs) const RETURNS ( val >= std::forward<RHS>(rhs) );
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator< (RHS&& rhs) const RETURNS ( val <  std::forward<RHS>(rhs) );
    template<typename RHS, EnableIf< !is_value_ptr<RHS>::value, 0 >...> auto operator> (RHS&& rhs) const RETURNS ( val >  std::forward<RHS>(rhs) );
    
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator==(U&& o) const RETURNS ( val == o.val )
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator!=(U&& o) const RETURNS ( val != o.val )
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator<=(U&& o) const RETURNS ( val <= o.val )
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator>=(U&& o) const RETURNS ( val >= o.val )
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator< (U&& o) const RETURNS ( val <  o.val )
    template<typename U, EnableIf< is_value_ptr<U>::value, 1 >...> auto operator> (U&& o) const RETURNS ( val >  o.val )
};
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator==( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs == rhs.val )
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator!=( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs != rhs.val )
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator<=( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs <= rhs.val )
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator>=( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs >= rhs.val )
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator< ( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs <  rhs.val )
template<typename LHS, typename T, EnableIf< !is_value_ptr<LHS>::value>...> auto operator> ( LHS&& lhs, value_ptr<T> const& rhs ) RETURNS ( lhs >  rhs.val )
// In some cases, we want different behavior based on phase
// Phases are types, and all_phase is the default
struct all_phases {};

struct empty {};

// For a given node type T, the default data type is T in all phases:
template<typename T>
struct data_type_all_phase {
    typedef T type;
};
template<typename T, typename phase=all_phases>
struct data_type:data_type_all_phase<T> {};

template<typename T, typename phase=all_phases>
using DataType = typename data_type<T, phase>::type;

// For a given node type T, the default legal child node types is T:
template<typename T>
struct child_types_all_phase {
    typedef type_list<T> types;
};
template<typename T, typename phase=all_phases>
struct child_types:child_types_all_phase<T> {};

template<typename T, typename phase=all_phases>
using ChildTypes = typename child_types<T, phase>::types;

template<typename T>
struct child_container_all_phase {
    template<typename U>
    using container = std::vector<U>;
};
template<>
struct child_container_all_phase<empty> {
    template<typename U>
    using container = empty;
};
template<typename T,typename phase=all_phases>
struct child_container:child_container_all_phase<T> {};
template<typename T,typename U,typename phase=all_phases>
using ChildContainer = typename child_container<U, phase>::template container<U>;

// All TreeBase<phase, Ts...> MUST be Tree<phase, Ts...>:
template<typename phase, typename...Ts>
struct TreeBase {
    virtual ~TreeBase() {}
    virtual TreeBase<phase, Ts...>* clone() const = 0;
};
template<typename phase>
struct MakeTreeBasePtr {
    template<typename... Ts>
    using Type = value_ptr< TreeBase<phase, Ts...> >;
};

template<typename T, typename phase=all_phases>
struct TypedTree {
    DataType<T, phase> data;
    ChildContainer< T, CopyTypes< ChildTypes<T>, MakeTreeBasePtr<phase>::template Type >, phase > children;
    template<typename U, typename=typename std::enable_if< std::is_constructible<DataType<T,phase>, U>::value>::type>
    TypedTree( U&& d ):data(std::forward<U>(d)) {};
    TypedTree():data() {};
};
template<typename phase, typename...Ts>
struct Tree:TreeBase<phase, Ts...> {
    typedef
    boost::variant< TypedTree< empty, phase >, TypedTree< Ts, phase >... >
    nodes;
    nodes node;
    virtual TreeBase<phase, Ts...>* clone() const override final {
        return new Tree<phase, Ts...>( *this );
    }
    template<typename U>
    TypedTree<U,phase>* get_node() {
        return boost::get< TypedTree<U, phase> >( &node );
    }
    template<typename U>
    TypedTree<U,phase> const* cget_node() const {
        return boost::get< TypedTree<U, phase> >( &node );
    }
    template<typename U>
    TypedTree<U,phase> const* get_node() const {
        return boost::get< TypedTree<U, phase> >( &node );
    }
    template<typename U>
    DataType<U, phase>* get_data() {
        auto* match = get_node<U>();
        if (!match)
            return nullptr;
        else
            return &match->data;
    }
    template<typename U>
    DataType<U, phase> const* cget_data() const {
        auto* match = get_node<U>();
        if (!match)
            return nullptr;
        else
            return &match->data;
    }
    template<typename U>
    DataType<U, phase> const* get_data() const {
        return cget_data();
    }
    template<typename U>
    auto get_children()->decltype( &get_node<U>()->children ) {
        auto* match = get_node<U>();
        if (!match)
            return nullptr;
        else
            return &match->children;
    }
    template<typename U>
    auto cget_children()->decltype( &get_node<U>()->children ) const {
        auto* match = get_node<U>();
        if (!match)
            return nullptr;
        else
            return &match->children;
    }
    template<typename U>
    auto get_children()->decltype( &get_node<U>()->children ) const {
        return cget_children<U>();
    }
    template<typename U, typename V>
    void set_type( V&& data ) {
        node = nodes(TypedTree<U, phase>( std::forward<V>(data) ));
    }
    template<typename U>
    void set_type() {
        node = nodes(TypedTree<U, phase>());
    }
};
template<typename phase, typename...Ts>
Tree<phase, Ts...>& FromBase( TreeBase<phase, Ts...>& base ) { return static_cast<Tree<phase, Ts...>&>(base); }
template<typename phase, typename...Ts>
Tree<phase, Ts...> const& FromBase( TreeBase<phase, Ts...> const& base ) { return static_cast<Tree<phase, Ts...> const&>(base); }

template<std::size_t n>
struct phase {};
struct phase0 {};

Tree< phase0, int, double > test;

template< typename phase_in, typename phase_out, typename T_in, typename Ts_out = type_list<T_in> >
struct tree_convert {
    typedef TypedTree< phase_in, T_in > in_type;
    typedef CopyTypes< Ts_out, MakeTreeBasePtr<phase_out>::template Type > out_types;
    typedef CopyTypes< out_types, boost::variant > out_var;
    typedef std::function< out_var( in_type const& ) > convert_func;
};

template<typename F>
struct handle_function;
template<typename R, typename... Args>
struct handle_function<std::function<R(Args...)>> {
    typedef R return_type;
    std::function<R(Args...)> func;
    R operator()( Args&&... args ) const {
        return func( std::forward<Args>(args)... );
    }
    handle_function( std::function<R(Args...)> const& f ):func(f) {}
    handle_function( std::function<R(Args...)> & f ):func(f) {}
    handle_function( std::function<R(Args...)> && f ):func(std::move(f)) {}
};
template<typename F>
struct return_type;
template<typename R, typename... Args>
struct return_type< std::function<R(Args...)> > {
    typedef R type;
};
template<typename F>
using ReturnType = typename return_type<typename std::decay<F>::type>::type;

template< typename... Fs >
struct multiplex_functions_helper {};
template< typename F0>
struct multiplex_functions_helper<F0>:
    handle_function<typename std::decay<F0>::type>
{
    typedef boost::variant< ReturnType<F0> > result_type;
    using handle_function<typename std::decay<F0>::type>::operator();
    template<typename F>
    multiplex_functions_helper( F&& f ):
        handle_function<typename std::decay<F0>::type>( std::forward<F>(f) )
    {}
};


template<typename F0, typename F1, typename... Fs>
struct multiplex_functions_helper<F0, F1, Fs...>:
    handle_function<typename std::decay<F0>::type>,
    multiplex_functions_helper<F1, Fs...>
{
    typedef boost::variant< ReturnType<F0>, ReturnType<F1>, ReturnType<Fs>... > result_type;
    using handle_function<typename std::decay<F0>::type>::operator();
    using multiplex_functions_helper<F1, Fs...>::operator();
    template<typename F, typename... Frest>
    multiplex_functions_helper( F&& f, Frest&&... fs ):
        handle_function<typename std::decay<F0>::type>( std::forward<F>(f) ),
        multiplex_functions_helper<F1, Fs...>( std::forward<Frest>(fs)... )
    {}
};
template< typename... Fs>
struct multiplex_functions:multiplex_functions_helper<Fs...>
{
    typedef typename multiplex_functions_helper<Fs...>::result_type result_type;
    template<typename... Args>
    result_type operator()(Args&&... args) const {
        return result_type(static_cast< multiplex_functions_helper<Fs...> const& >(*this)( std::forward<Args>(args)... ));
    }
    template<typename... F2s>
    multiplex_functions( F2s&&... fs ):
        multiplex_functions_helper<Fs...>( std::forward<F2s>(fs)... )
    {}
};
template<typename... Fs>
multiplex_functions<Fs...> make_multiplex( Fs&&... fs ) {
    return multiplex_functions<Fs...>( std::forward<Fs>(fs)... );
}

std::function< bool(int) > int_test = []( int x )->bool {
    std::cout << "int of value " << x << "\n";
    return true;
};
std::function< char(double) > double_test = []( double x )->char {
    std::cout << "double of value " << x << "\n";
    return 'a';
};
std::function< empty(char) > char_test = []( char x )->empty {
    std::cout << "char of value " << x << "\n";
    return empty();
};
std::function< int(bool) > bool_test = []( bool x )->int {
    std::cout << "bool of value " << (x?"true":"false") << "\n";
    return 7;
};

auto multi = make_multiplex( int_test, double_test );

struct printer {
    template<typename T>
    void operator()( T const* t ) const {
        std::cout << t;
        if (t)
            std::cout << "=" << *t;
        std::cout << "\n";
    }
};

template<typename... Ts, typename Tree, typename Print>
void dump_data(Tree&& tree, Print&& print = printer()) {
    std::cout << "--\n";
    int _[] = {
        ( print( tree.template get_data<Ts>() ), 0 )...
    };
}

void test1() {
    dump_data<int, double>( test, printer() );
    test.set_type<int>( 3.0 );
    dump_data<int, double>( test, printer() );
    test.set_type<double>( 7 );
    dump_data<int, double>( test, printer() );
    std::cout << "test1 complete\n";
}

void test2() {
    multi(7);
    multi(3.13);
    std::cout << "test2 complete\n";
}

struct print {
    typedef void result_type;
    template<typename T>
    void operator()(T&& t) const {
        std::cout << std::forward<T>(t);
    }
};

void test3() {
    boost::variant<int, double> v1 = 7;
    boost::variant<int, double> v2 = 3.14;
    boost::variant<bool, char> r1 = apply_visitor( multi, v1 );
    boost::variant<bool, char> r2 = apply_visitor( multi, v2 );
    boost::apply_visitor( print(), r1 );
    std::cout << "\n";
    boost::apply_visitor( print(), r2 );
    std::cout << "\n";
    std::cout << "test3 complete";
}

int main() {
    test1();
    test2();
    test3();
}