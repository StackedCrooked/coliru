#include <iostream>
#include <string>
#include <vector>

template<class T>
struct aligned_pod {
    alignas(T) char data[sizeof(T)];
    
    void*       pvoid()       { return &data; }
    const void* pvoid() const { return &data; }
    T&       get()       { return *static_cast<T*>      (pvoid()); }
    const T& get() const { return *static_cast<const T*>(pvoid()); }
    operator const T& () const { return get(); }
    operator       T& ()       { return get(); }
    
    template<class ...Args>
    void construct(Args&&... args) {
        new (pvoid()) T(std::forward<Args>(args)...);
    }
    void destroy() { get().~T(); }
    
    friend std::ostream& operator<< (std::ostream& ost, const aligned_pod& pod) {
        return ost << pod.get();
    }
};

struct nullopt_t {} nullopt;
struct in_place_t {} in_place;

template<class T>
class optional {
    aligned_pod<T> data;
    bool empty_ = true;


    void clear() { if(!empty_) data.destroy(); empty_ = true; }
    template<class ...Args>
    void construct(Args&&... args) {
        clear();
        data.construct(std::forward<Args>(args)...);
        empty_ = false;
    }
    template<class Arg>
    void assign(Arg&& arg) {
        if(empty_) construct(std::forward<Arg>(arg));
        else data.get() = std::forward<Arg>(arg);
        empty_ = false;
    }
    
public:
    using value_type = T;
    
    optional() = default;
    optional(nullopt_t) : optional() {};
    optional(const optional& other) : empty_(other.empty_) {
        if(!empty_) data.construct(*other);    
    }
    optional(optional&& other) : empty_(other.empty_) {
        if(!empty_) data.construct(std::move(*other));
    }
    optional(const T& data) : empty_(false) { 
        construct(data); 
    }
    optional(T&& data) : empty_(false) { 
        construct(std::move(data)); 
    }
    template<class ...Args>
    explicit optional(in_place_t, Args&&... args): empty_(false) { 
        construct(std::forward<Args>(args)...); 
    }
    template<class U, class ...Args>
    explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args): empty_(false) { 
        construct(ilist, std::forward<Args>(args)...); 
    }
    
    T&       value()       { return data.get(); }
    const T& value() const { return data.get(); }	
    template< class U >
    T value_or( U&& value ) const {
        return empty_ ? T{std::forward<U>(value)} : data.get();
    }

    T&       operator*()       { return value(); }
    const T& operator*() const { return value(); }
    T*       operator->()       { return &value(); }
    const T* operator->() const { return &value(); }
    
    optional& operator=(nullopt_t ){ clear(); return *this; }		
    optional& operator=(const optional& other ) {
        if(other.empty_) clear();
        else assign(*other);
        return *this;
    }
    optional& operator=( optional&& other ) {
        if(other.empty_) clear();
        else assign(std::move(*other));
        return *this;
    }
    template< class U >
    optional& operator=( U&& value ) {
        assign(std::forward<U>(value));
        return *this;
    }
    explicit operator bool() const { 
        return !empty_; 
    }
    
    ~optional() { clear(); }
    
    void swap (optional& other) {
        if(empty_ && other.empty_) return;
        
        if(empty_) {
            *this = std::move(other);
            other.clear();
            return;
        }
        if(other.empty_) {
            other = std::move(*this);
            this->clear();
            return;
        }
        swap(**this, *other); 
    }
    
    template< class... Args >
    void emplace( Args&&... args ) {
        construct(std::forward<Args>(args)...);        
    }
    	
    template< class U, class... Args >
    void emplace( std::initializer_list<U> ilist, Args&&... args ) {
        construct(ilist, std::forward<Args>(args)...);
    }
};

template< class T >
bool operator==( const optional<T>& lhs, const optional<T>& rhs ) {
    if(!lhs && !rhs) return true;
    else if(lhs && rhs) return *lhs == *rhs;
    else return false;
}		
template< class T >
bool operator==( const optional<T>& opt, nullopt_t ) {
    return !opt;
}
template< class T >
bool operator==( nullopt_t, const optional<T>& opt ){
    return !opt;
}
template< class T >
bool operator==( const optional<T>& opt, const T& v ) {
    if(!opt) return false;
    else return *opt == v;
}
template< class T >	
bool operator==(  const T& v, const optional<T>& opt ) {
    if(!opt) return false;
    else return *opt == v;
}

/* provide output operator just for fun */
template<class T>
std::ostream& operator <<  (std::ostream& str, const optional<T>& opt) {
    if(!opt) str << "nothing";
    else str << "just " << *opt;
    return str;
}

int main()
{
    optional<std::string> opt;                        /* opt is empty */
    std::cout << opt << std::endl;                    /* >$ nothing */
    opt = "Hi";                                       /* opt is "Hi" */
    std::cout << opt << std::endl;                    /* >$ just Hi */
    opt = nullopt;                                    /* opt is empty */
    std::cout << opt << std::endl;                    /* >$ nothing */
    opt = "Hi";                                       /* opt is "Hi" */
    auto opt2 = opt;                                  /* opt2 is "Hi" */
    std::cout << opt2 << std::endl;                   /* >$ just Hi */
    auto opt3 = std::move(opt);                       /* opt3 is "Hi", opt is garbage (!!!) */
    std::cout << opt3 << std::endl;                   /* >$ just Hi */
    opt3 = nullopt;                                   /* opt3 is empty */
    std::cout << opt3 << std::endl;                   /* >$ nothing */
    std::cout << opt3.value_or("smth") << std::endl;  /* >$ smth */
    std::cout << opt2.value_or("smth") << std::endl;  /* >$ Hi   */
    std::cout << sizeof(opt) << std::endl;            /* no dynamic memory is use so sizeof is the complete size of the object */
                                                      /* = sizeof(std::string) + sizeof(bool) + few bytes of alignment */
                                                      /* prints 16 for g++-4.8, may be different*/
}
