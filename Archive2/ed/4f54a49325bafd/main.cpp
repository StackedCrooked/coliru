#include <iostream>

template<class ...Elements> union aligned_storage;
template<class H, class ...T> union aligned_storage<H, T...> {
    H head;
    aligned_storage<T...> tail;
    
    aligned_storage(){}
    ~aligned_storage(){}
};
template<> union aligned_storage<> {};

template<size_t Ix, class ...Elements> struct aligned_storage_visitor;

template<size_t Ix, class HElement, class ...TElements>
struct aligned_storage_visitor<Ix, HElement, TElements...> {
    template<class F>
    inline static auto visit(F f, size_t RealIx, aligned_storage<HElement, TElements...>& as) -> decltype(auto) {
        return (RealIx == Ix) ? f(as.head) : aligned_storage_visitor<Ix-1, TElements...>::visit(f, RealIx, as.tail);
    }
    
    template<class F>
    inline static auto visit(F f, size_t RealIx, const aligned_storage<HElement, TElements...>& as) -> decltype(auto) {
        return (RealIx == Ix) ? f(as.head) : aligned_storage_visitor<Ix-1, TElements...>::visit(f, RealIx, as.tail);
    }
};

template<class HElement, class ...TElements>
struct aligned_storage_visitor<0, HElement, TElements...> {
    template<class F>
    inline static auto visit(F f, size_t RealIx, aligned_storage<HElement, TElements...>& as) -> decltype(auto) {
        return f(as.head);
    }
    
    template<class F>
    inline static auto visit(F f, size_t RealIx, const aligned_storage<HElement, TElements...>& as) -> decltype(auto) {
        return f(as.head);
    }
};

template<size_t Ix, class ...Elements> struct aligned_storage_access_helper;
template<size_t Ix, class HEl, class ...TEls>
struct aligned_storage_access_helper<Ix, HEl, TEls...> {
    inline static auto ptr(aligned_storage<HEl, TEls...>& as) {
        return aligned_storage_access_helper<Ix-1, TEls...>::ptr(as.tail);
    }
        
    inline static auto ptr(const aligned_storage<HEl, TEls...>& as) {
        return aligned_storage_access_helper<Ix-1, TEls...>::ptr(as.tail);
    }
};
template<class HEl, class ...TEls>
struct aligned_storage_access_helper<0, HEl, TEls...> {
    inline static auto ptr(aligned_storage<HEl, TEls...>& as) {
        return &as.head;
    }
        
    inline static auto ptr(const aligned_storage<HEl, TEls...>& as) {
        return &as.head;
    }
};

template<size_t Ix, class ...Elements>
inline auto get_ptr(aligned_storage<Elements...>& as) {
    return aligned_storage_access_helper<Ix, Elements...>::ptr(as);
}

template<size_t Ix, class ...Elements>
inline auto get_ptr(const aligned_storage<Elements...>& as) {
    return aligned_storage_access_helper<Ix, Elements...>::ptr(as);
}

template<class T, class ...Args>
inline void construct(T* self, Args&&... args) {
    new (self) T { std::forward<Args>(args)... };
}

template<class T>
inline void destruct(T* self) {
    self -> ~T();
}

template<class T, class ...Elements> struct find_t;
template<class H, class ...TEls> struct find_t<H, H, TEls...> {
    enum{ value = 0 };
};
template<class H, class T, class ...TEls> struct find_t<T, H, TEls...> {
    enum{ value = find_t<T, TEls...>::value + 1 };
};

template<class T, class ...Elements> struct contains_t;
template<class H, class ...TEls> struct contains_t<H, H, TEls...> {
    enum{ value = true };
};
template<class H, class T, class ...TEls> struct contains_t<T, H, TEls...> {
    enum{ value = contains_t<T, TEls...>::value };
};
template<class T> struct contains_t<T> {
    enum{ value = false };
};

template<class T, class ...Elements> struct contains2_t;
template<class H, class ...TEls> struct contains2_t<H, H, TEls...> {
    enum{ value = contains_t<H, TEls...>::value };
};
template<class H, class T, class ...TEls> struct contains2_t<T, H, TEls...> {
    enum{ value = contains2_t<T, TEls...>::value };
};
template<class T> struct contains2_t<T> {
    enum{ value = false };
};
template<class T, class A> struct contains2_t<T, A> {
    enum{ value = false };
};
template<class T> struct contains2_t<T, T> {
    enum{ value = false };
};

template<size_t N>
struct construct_variant_t{};

template<class ...Elements>
class variant {
    aligned_storage<Elements...> data_;
    unsigned char ix_;
    
    
public:
    template<class F>
    auto select(F f) -> decltype(auto) {
        return aligned_storage_visitor<sizeof...(Elements)-1, Elements...>::visit(f, ix_, data_);
    }
    
    template<class F>
    auto select(F f) const -> decltype(auto) {
        return aligned_storage_visitor<sizeof...(Elements)-1, Elements...>::visit(f, ix_, data_);
    }
    
private:
    template<size_t N, class ...CArgs>
    void construct(construct_variant_t<N>, CArgs&&... cargs) {
        ::construct( get_ptr<N>(data_), std::forward<CArgs>(cargs)... );
        ix_ = N;        
    }
    template<class U>
    void construct(const U& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        enum{ N = find_t<U, Elements...>::value };
        construct(construct_variant_t<N>{}, other);
    }
    template<class U>
    void construct(U&& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        enum{ N = find_t<U, Elements...>::value };
        construct(construct_variant_t<N>{}, std::move(other));
    }
    void destruct() {
        select([](auto&& h){ destruct(&h); });
    }
    
public:
    template<size_t N, class ...CArgs>
    variant(construct_variant_t<N> cv, CArgs&&... cargs) {
        construct(cv, std::forward<CArgs>(cargs)...);
    }
    template<class U>
    variant(const U& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        construct(other);      
    }
    template<class U>
    variant(U&& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        construct(std::move(other));      
    }
    variant(const variant& other) {
        other.select([this](auto&& h){ this->construct(h); });
    }
    variant(variant&& other) {
        other.select([this](auto&& h){ this->construct(std::move(h)); });
    }
    
    template<size_t N>
    variant& operator=(construct_variant_t<N> cv) {
        destruct();
        construct(cv);
        return *this;
    }
    template<class U>
    typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value, variant&>::type operator=(const U& other) {
        destruct();
        construct(other);      
        return *this;
    }
    template<class U>
    typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value, variant&>::type operator=(U&& other) {
        destruct();
        construct(std::move(other));      
        return *this;
    }
    variant& operator=(const variant& other) {
        destruct();
        other.select([this](auto&& h){ this->construct(h); });
        return *this;
    }
    variant& operator=(variant&& other) {
        destruct();
        other.select([this](auto&& h){ this->construct(std::move(h)); });
        return *this;
    }
    
    ~variant() {
        destruct();
    }
    
    template<size_t N, class ...CArgs>
    void emplace(construct_variant_t<N> cv, CArgs&&... cargs) {
        destruct();
        construct(cv, std::forward<CArgs>(cargs)...);
    }
    template<class U>
    void emplace(const U& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        destruct();
        construct(other);      
    }
    template<class U>
    void emplace(U&& other, typename std::enable_if<contains_t<U, Elements...>::value && !contains2_t<U, Elements...>::value>::type* = 0) {
        destruct();
        construct(std::move(other));      
    }
    
    friend bool operator<(const variant& lhv, const variant& rhv) {
        if(lhv.ix_ < rhv.ix_) return true;
        if(rhv.ix_ < lhv.ix_) return false;
        return lhv.select([&](auto&& lhvv){
            return rhv.select([&](auto&& rhvv) {
                return lhvv < rhvv;
            });
        });
    }
    
    friend bool operator ==(const variant& lhv, const variant& rhv) {
        if(lhv.ix_ != rhv.ix_) return false;
        return lhv.select([&](auto&& lhvv){
            return rhv.select([&](auto&& rhvv) {
                return lhvv == rhvv;
            });
        });
    }
    
    friend std::ostream& operator <<(std::ostream& ost, const variant& v) {
        std::cout << v.ix_ << std::endl;
        return v.select([&ost](auto&& vv) -> decltype(auto){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            return ost << vv;
        });
    }
    
};

int main() {
    variant<int, double, char> v = construct_variant_t<0>{};
    variant<int, double, char> v2{ construct_variant_t<0>{} };
    variant<int, double, char> c = 2.0;
    variant<int, double, char> c2{ 3.14 };
    
    std::cout << (v == c) << std::endl;
    std::cout << v << std::endl;
    std::cout << c << std::endl;
    std::cout << v2 << std::endl;
    std::cout << c2 << std::endl;
}