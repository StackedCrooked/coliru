#include <iostream>
#include <typeinfo>
#include <type_traits>

namespace internal {
    //
    // Helper to determine position of a type in a list of types
    //
    template <typename X, typename... Types>
    struct position_impl;

    template <typename X>
    struct position_impl<X> { static size_t const value = 1; };

    template <typename X, typename... Types>
    struct position_impl<X, X, Types...> { static size_t const value = 0; };
    
    template <typename X, typename T, typename... Types>
    struct position_impl<X, T, Types...> { static size_t const value = 1 + position_impl<X, Types...>::value; };

    template <typename X, typename... Types>
    struct position {
        static size_t const value = position_impl<X, Types...>::value;
        static_assert(value < sizeof...(Types), "Unknown Type");
    }; // struct position

    //
    // Helpers to determine the maximum size and alignment of a list of types
    // (because despite some claims, std::aligned_union does not seem to be in <type_traits>)
    //
    inline constexpr size_t max(size_t left, size_t right) { return left >= right ? left : right; }
    
    template <typename T>
    constexpr size_t max_size() { return sizeof(T); }

    template <typename T0, typename T1, typename... Types>
    constexpr size_t max_size() { return max(sizeof(T0),  max_size<T1, Types...>()); }
    
    template <typename T>
    constexpr size_t max_alignment() { return alignof(T); }

    template <typename T0, typename T1, typename... Types>
    constexpr size_t max_alignment() { return max(alignof(T0), max_alignment<T1, Types...>()); }
    
    template <size_t Len, typename... Types>
    struct aligned_union {
        using type = typename std::aligned_storage<max(Len, max_size<Types...>()), max_alignment<Types...>()>::type;
    }; // struct aligned_union

    //
    // Apply
    //
    template <typename T, typename F, typename S>
    void apply_unary_impl(F& functor, S& storage) {
        T& t = reinterpret_cast<T&>(storage);
        functor(t);
    } // apply_unary_impl
    
    template <typename... Types, typename F, typename S>
    void apply_unary(F& functor, S& storage, size_t const tag) {
        using Applier = void (*)(F&,S&);
        static Applier const appliers[] = { &apply_unary_impl<Types, F, S>... };

        Applier const a = appliers[tag];
        a(functor, storage);
    } // apply_unary

    template <typename T, typename F, typename S>
    void apply_binary_impl(F& functor, S& left, S& right) {
        T& typed_left = reinterpret_cast<T&>(left);
        T& typed_right = reinterpret_cast<T&>(right);
        functor(typed_left, typed_right);
    } // apply_binary_impl

    template <typename... Types, typename F, typename S>
    void apply_binary(F& functor, S& left, S& right, size_t const tag) {
        using Applier = void (*)(F&,S&);
        static Applier const appliers[] = { &apply_binary_impl<Types, F, S>... };

        Applier const a = appliers[tag];
        a(functor, left, right);
    } // apply_binary

    //
    // Some Visitors
    //
    template <typename T>
    struct MoveInitializer {
        MoveInitializer(T&& t): item(std::move(t)) {}
        T item;
        
        void operator()(T& t) { new (&t) T(std::move(item)); }
        
        template <typename U>
        void operator()(U&) {}
    }; // struct MoveInitializer
    
    template <typename T>
    struct CopyInitializer {
        CopyInitializer(T const& t): ref(t) {}
        T const& ref;
        
        void operator()(T& t) { new (&t) T(ref); }
        
        template <typename U>
        void operator()(U&) {}
    }; // struct CopyInitializer
    
    struct MoveConstructer {
        template <typename T>
        void operator()(T& left, T& right) { new (&left) T(std::move(right)); }
    }; // struct MoveConstructer

    struct CopyConstructer {
        template <typename T>
        void operator()(T& left, T& right) { new (&left) T(right); }
    }; // struct CopyConstructer

    struct Deleter {
        template <typename T>
        void operator()(T& t) { t.~T(); }
    }; // struct Deleter
    
} // namespace internal

template <typename H, typename... Tail>
class variant {
public:
    variant(): tag(0) { new (&storage) H{}; }

    template <typename T>
    variant(T&& t): tag(internal::position<T, H, Tail...>::value) {
        internal::MoveInitializer<T> m{std::move(t)}; internal::apply_unary<H, Tail...>(m, storage, tag);
    }

    template <typename T>
    variant(T const& t): tag(internal::position<T, H, Tail...>::value) {
        internal::CopyInitializer<T> c{t}; internal::apply_unary<H, Tail...>(c, storage, tag);
    }

    variant(variant&& other): tag(other.tag) { internal::MoveConstructer m; internal::apply_binary<H, Tail...>(m, storage, other.storage, tag); }

    variant(variant const& other): tag(other.tag) { internal::CopyConstructer c; internal::apply_binary<H, Tail...>(c, storage, other.storage, tag); }

    variant& operator=(variant other) {
        using std::swap;
        swap(*this, other);
        return *this;
    } // operator=

    ~variant() { internal::Deleter d; internal::apply_unary<H, Tail...>(d, storage, tag); }

    size_t which() const { return tag; }

    template <typename T>
    T* get() {
        static size_t const pos = internal::position<T, H, Tail...>::value;
        return pos == tag ? reinterpret_cast<T*>(&storage) : nullptr;
    }

    template <typename T>
    T const* get() const {
        static size_t const pos = internal::position<T, H, Tail...>::value;
        return pos == tag ? reinterpret_cast<T const*>(&storage) : nullptr;
    }

private:
    using Storage = typename internal::aligned_union<0, H, Tail...>::type;

    size_t tag;
    Storage storage;
}; // class variant

template <typename R = void>
struct static_visitor { using result_type = R; };

//
// Visitation (unary)
//
namespace internal {
    template <typename Visitor, typename Variant>
    struct UnaryApplier {
        using result_type = typename Visitor::result_type;

        UnaryApplier(Visitor& visitor, Variant& variant): visitor(visitor), variant(variant) {}
        Visitor& visitor;
        Variant& variant;
        
        template <typename T>
        auto apply() -> result_type { return visitor(*variant.template get<T>()); }
    }; // struct UnaryApplier
} // namespace internal

template <typename V, typename T0, typename... Types>
auto apply_unary_visitor(V&& visitor, variant<T0, Types...>& v0) -> typename V::result_type {
    using result_type = typename V::result_type;

    using Variant = variant<T0, Types...>;
    using Applier = internal::UnaryApplier<V, Variant>;
    using Member = result_type (Applier::*)();

    static Member const members[] = {
        (&Applier::template apply<T0>), 
        (&Applier::template apply<Types>)...
    };

    Member const m = members[v0.which()];
    Applier a{visitor, v0};
    return (a.*m)();
} // apply_unary_visitor

//
// Visitation (n-ary)
//
namespace internal {
    template <typename Visitor, typename T>
    struct NaryVisitor {
        using result_type = typename Visitor::result_type;
        
        NaryVisitor(Visitor& visitor, T& t): visitor(visitor), ref(t) {}
        Visitor& visitor;
        T& ref;
        
        template <typename... Args>
        auto operator()(Args&&... args) -> result_type {
            return visitor(ref, std::forward<Args>(args)...);
        } // apply
    }; // struct NaryVisitor
    
    template <typename Visitor, typename T0, typename... Types, typename... Vs>
    auto apply_nary_visitor_impl(Visitor& visitor, variant<T0, Types...>&& v0, Vs&&... vs) -> typename Visitor::result_type;
    
    template <typename Visitor, typename Variant>
    struct NaryApplier {
        using result_type = typename Visitor::result_type;
        
        NaryApplier(Visitor& visitor, Variant& variant): visitor(visitor), variant(variant) {}
        Visitor& visitor;
        Variant& variant;
        
        template <typename T>
        auto apply() -> result_type { return visitor(*variant.template get<T>()); }
        
        template <typename T, typename V0, typename... Vs>
        auto apply(V0&& v0, Vs&&... vs) -> result_type {
            NaryVisitor<Visitor, T> nary{visitor, *variant.template get<T>()};
            return apply_nary_visitor_impl(nary, std::forward<V0>(v0), std::forward<Vs>(vs)...);
        }
    }; // struct NaryApplier
    
    template <typename Visitor, typename T0, typename... Types, typename... Vs>
    auto apply_nary_visitor_impl(Visitor& visitor, variant<T0, Types...>& v0, Vs&&... vs) -> typename Visitor::result_type {
        using result_type = typename Visitor::result_type;

        using Variant = variant<T0, Types...>;
        using Applier = internal::NaryApplier<Visitor, Variant>;
        using Member = result_type (Applier::*)(Vs&&...);
    
        static Member const members[] = {
            (&Applier::template apply<T0, Vs...>), 
            (&Applier::template apply<Types, Vs...>)...
        };

        Member const m = members[v0.which()];
        Applier a{visitor, v0};
        return (a.*m)(std::forward<Vs>(vs)...);
    } // apply_nary_visitor_impl
    
} // namespace internal

template <typename Visitor, typename... Variants>
auto apply_nary_visitor(Visitor&& visitor, Variants&&... vs) -> typename Visitor::result_type {
    return internal::apply_nary_visitor_impl(visitor, std::forward<Variants>(vs)...);
} // apply_nary_visitor

//
// Test
//
struct Printer: static_visitor<> {
    template <typename T>
    void operator()(T const& t) { std::cout << typeid(T).name() << " " << t << "\n"; }
};

struct DualPrinter: static_visitor<> {
    template <typename T, typename U>
    void operator()(T const& t, U const& u) { std::cout << typeid(T).name() << " " << t << ", " << typeid(U).name() << " " << u << "\n"; }
}; // struct DualPrinter

int main() {
    variant<int, std::string> v0;
    apply_visitor(Printer{}, v0);
    
    variant<int, std::string> v1{std::string("Hello, World!")};
    apply_visitor(DualPrinter{}, v0, v1);
}
