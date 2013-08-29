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
};
template<typename phase>
struct MakeTreeBase {
    template<typename... Ts>
    using Type = TreeBase<phase, Ts...>;
};

template<typename T, typename phase=all_phases>
struct TypedTree {
    DataType<T, phase> data;
    ChildContainer< T, CopyTypes< ChildTypes<T>, MakeTreeBase<phase>::template Type >, phase > children;
    template<typename U>
    TypedTree( U&& d ):data(std::forward<U>(d)) {};
    TypedTree():data() {};
};
template<typename phase, typename...Ts>
struct Tree:TreeBase<phase, Ts...> {
    boost::variant< TypedTree< empty, phase >, TypedTree< Ts, phase >... > node;
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
        node = TypedTree<U, phase>( std::forward<V>(data) );
    }
    template<typename U>
    void set_type() {
        node = TypedTree<U, phase>();
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

struct printer {
    template<typename T>
    void operator()( T const* t ) const {
        std::cout << t;
        if (t)
            std::cout << *t;
        std::cout << "\n";
    }
};

template<typename... Ts, typename Tree, typename Print>
void dump_state(Tree&& tree, Print&& print = printer()) {
    do_in_order( [&]{
        print( tree.template get_data<Ts>() );
    }... );
}

int main() {
    dump_data<int, double>( test, printer );
    std::cout << "test complete\n";
}