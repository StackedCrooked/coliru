#include <memory>
#include <type_traits>
#include <utility>
#include <sstream>
#include <cstdarg>


#define alignof __alignof

namespace mpd {



static const int overload_choice_max = 10;
template<int num> struct overload_choice;
template<> struct overload_choice<overload_choice_max> {};
template<int num> struct overload_choice : public overload_choice<num+1> {};

template<class allocator>
struct alloc_array_deleter {
    alloc_array_deleter(allocator& a, int c) : al(&a), count(c) {}
    template<class U>
    void operator()(U* p) {al->deallocate(p, count);}    
private:
    allocator* al;
    int count;
};
template<class allocator>
struct alloc_single_deleter {
    alloc_single_deleter(allocator& a) : al(&a) {}
    template<class U>
    void operator()(U* p) {al->deallocate(p);}    
private:
    allocator al;
};

template<class fallback, class deleter> typename deleter::pointer get_ptr_type(deleter*) {return 0;}
template<class fallback> fallback get_ptr_type(void*) {return 0;}

template<class T, class deleter>
struct raw_allocation {
    typedef decltype(get_ptr_type<T*>(std::declval<deleter*>())) pointer;
    raw_allocation() : free(), ptr() {}
    raw_allocation(raw_allocation&& rhs) : free(rhs.free),ptr(rhs.ptr) {rhs.ptr = nullptr;}
    raw_allocation(const deleter& d) : free(d), ptr() {}
    raw_allocation(deleter&& d) : free(std::move(d)), ptr() {}
    raw_allocation(T* p) : free(), ptr(p) {}
    raw_allocation(T* p, const deleter& d) : free(d), ptr(p) {}
    raw_allocation(T* p, deleter&& d) : free(std::move(d)), ptr(p) {}
    raw_allocation(char* p) : free(), ptr(reinterpret_cast<T*>(p)) {}
    raw_allocation(char* p, const deleter& d) : free(d), ptr(reinterpret_cast<T*>(p)) {}
    raw_allocation(char* p, deleter&& d) : free(std::move(d)), ptr(reinterpret_cast<T*>(p)) {}
    raw_allocation& operator=(raw_allocation&& rhs) {do_free(); free=rhs.free; ptr=rhs.ptr; rhs.ptr=nullptr; return *this;}
    raw_allocation& operator=(T* p) {do_free(); ptr=p; return *this;}
    raw_allocation& operator=(char* p) {do_free(); ptr=reinterpret_cast<T*>(p); return *this;}
    ~raw_allocation() {do_free();}
    T* operator->() {return ptr;}
    T& operator*() {return *ptr;}
    T* get() {return ptr;}
    operator T*() {return ptr;}
    T* release() {T*t=ptr; ptr=nullptr; return t;}
private:
    void do_free() {if(ptr)free(reinterpret_cast<char*>(ptr));ptr=nullptr;}
    deleter free;
    T* ptr;
};
template<class interface, class allocator>
raw_allocation<interface, alloc_array_deleter<typename allocator::template rebind<char>::other>> safe_alloc(allocator& alloc, size_t count=1)
{
    typedef typename allocator::template rebind<char>::other real_allocator;
    real_allocator al(alloc);
    return {reinterpret_cast<interface*>(al.allocate(count)), alloc_array_deleter<real_allocator>(al,count)};
}
template<class interface, class allocator>
raw_allocation<interface, alloc_array_deleter<typename allocator::template rebind<char>::other>> reuse_alloc(interface* ptr, allocator& alloc, size_t count=1)
{
    typedef typename allocator::template rebind<char>::other real_allocator;
    real_allocator al(alloc);
    return {ptr, alloc_array_deleter<real_allocator>(al,count)};
}

struct use_copy {
    template<class T>
    const T& operator()(const T& t) {return t;}
};
struct use_move {
    template<class T>
    T&& operator()(T& t) {return std::move(t);}
};

namespace detail {
//allocator is a char allocator
template<class interface, class allocator>
struct dispatch_interface {
    virtual ~dispatch_interface() {}
    virtual interface* get()=0;
    virtual const interface* get() const=0;
    virtual size_t get_size() const=0;
    virtual dispatch_interface* construct(allocator& al, dispatch_interface* buffer, use_copy)=0;
    virtual dispatch_interface* construct(allocator& al, dispatch_interface* buffer, use_move)=0;
    virtual dispatch_interface* assign(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, use_copy)=0;
    virtual dispatch_interface* assign(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, use_move)=0;
    virtual bool equals(const dispatch_interface* other) const=0;
};

template<class T> auto equals(const T& lhs, const T& rhs, overload_choice<1>) -> decltype(lhs==rhs) {return lhs==rhs;}
template<class T> bool equals(const T&, const T&, overload_choice<2>) {return false;}

//allocator is a char allocator
template<class T, class interface, class allocator>
struct dispatch_implementation : public dispatch_interface<interface,allocator> {
protected:
    typedef dispatch_interface<interface,allocator> dispatch_interface;
    T data;
public:
    dispatch_implementation(const dispatch_implementation&) = default;
    dispatch_implementation(dispatch_implementation&& rhs) : data(std::move(rhs.data)) {}
    dispatch_implementation& operator=(const dispatch_implementation&) = default;
    dispatch_implementation& operator=(dispatch_implementation&& rhs) {data=std::move(rhs.data); return *this;}
    template<class...U>
    dispatch_implementation(U&&... rhs) : data(std::forward<U>(rhs)...) {}
    virtual ~dispatch_implementation() {}
    virtual interface* get() {return &data;}
    virtual const interface* get() const {return &data;}
    virtual size_t get_size() const {return sizeof(*this);}
    virtual dispatch_interface* construct(allocator& al, dispatch_interface* buffer, use_copy forward)
    {al.construct(reinterpret_cast<dispatch_implementation*>(buffer), forward(*this)); return buffer;}
    virtual dispatch_interface* construct(allocator& al, dispatch_interface* buffer, use_move forward)
    {al.construct(reinterpret_cast<dispatch_implementation*>(buffer), forward(*this)); return buffer;}
    virtual dispatch_interface* assign(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, use_copy forward)
    {return assign_(al, other, dyn_size, buffer, buf_size, forward);}
    virtual dispatch_interface* assign(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, use_move forward) 
    {return assign_(al, other, dyn_size, buffer, buf_size, forward);}
    template<class U>
    auto assign(U&& v)->decltype(&(data=v)) {return data=v;}
    virtual bool equals(const dispatch_interface* other) const
    {
        const dispatch_implementation* same_other = dynamic_cast<const dispatch_implementation*>(other);
        if (same_other)
            return detail::equals(data, same_other->data, overload_choice<0>());
        return false;
    }
protected:
    template<class forward_type>
    dispatch_interface* assign_(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, forward_type forward)
    {
        dispatch_implementation* same_other = dynamic_cast<dispatch_implementation*>(other);
        if (same_other) 
            return assign_value_(al, same_other, dyn_size, buffer, buf_size, forward, std::is_copy_assignable<T>());
        else
            return overwrite_(al, other, dyn_size, buffer, buf_size, forward);
    }
        
    template<class forward_type>
    dispatch_interface* assign_value_(allocator&, dispatch_implementation* other, size_t&, dispatch_interface*, size_t, forward_type forward, std::true_type)
    {data = forward(other->data); return other;}

    template<class forward_type>
    dispatch_interface* assign_value_(allocator& al, dispatch_implementation* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, forward_type forward, std::false_type)
    {return overwrite_(al, other, dyn_size, buffer, buf_size, forward);}
        
    template<class forward_type>
    dispatch_interface* overwrite_(allocator& al, dispatch_interface* other, size_t& dyn_size, dispatch_interface* buffer, size_t buf_size, forward_type forward)
    {
        dispatch_interface* r;
        if (other)
            other->~dispatch_interface();
        if (other!=buffer && dyn_size >= sizeof(*this)) {
            r = construct(al, other, forward);
        } else if (buf_size >= sizeof(*this)) {
            r = construct(al, buffer, forward);
        } else {
            if (other!=buffer)
                al.deallocate(reinterpret_cast<char*>(other), dyn_size);
            typename allocator::template rebind<dispatch_implementation>::other al2(al);
            auto raw = safe_alloc<dispatch_implementation>(al2, sizeof(dispatch_implementation));
            dyn_size = sizeof(dispatch_implementation);
            construct(al, raw, forward);
            r = raw.release();
        }
        return r;
    }
};
}//namespace detail

template<class interface, size_t given_buf_size=32, class given_allocator=std::allocator<interface>>
class value_ptr {
    typedef typename given_allocator::template rebind<char>::other char_allocator;
    typedef detail::dispatch_interface<interface, char_allocator> dispatch_interface;

    char_allocator al;
    dispatch_interface* implementation;
    typename std::aligned_storage<given_buf_size<sizeof(size_t)?sizeof(size_t):given_buf_size, alignof(interface)>::type buffer;
    dispatch_interface* get_buf() {return reinterpret_cast<dispatch_interface*>(&buffer);}
    const dispatch_interface* get_buf() const {return reinterpret_cast<const dispatch_interface*>(&buffer);}
    size_t& dynamic_size() {return reinterpret_cast<size_t&>(buffer);}

    template<class T, class U>
    auto convert_assign_impl(detail::dispatch_implementation<T,interface,char_allocator> ptr, U&& v, overload_choice<1>) -> decltype(ptr->assign(std::forward<U>(v)))
    {return ptr->assign(v);}
    template<class T, class U>
    void convert_assign_impl(detail::dispatch_implementation<T,interface,char_allocator>, U&& v, overload_choice<2>)
    {
        dispatch_interface* temp = implementation;
        al.destroy(implementation);
        implementation = nullptr;
        allocate(temp, detail::dispatch_implementation<T,interface,char_allocator>(std::forward<U>(v)));
        dynamic_size() = sizeof(detail::dispatch_implementation<T,interface,char_allocator>);
        implementation = temp;
    }
    void move_noalloc_(value_ptr&& rhs) {
        if (rhs.implementation) {
            dispatch_interface* old = implementation;
            implementation = nullptr;
            implementation = rhs.implementation->assign(al, old, dynamic_size(), get_buf(), sizeof(buffer), use_move());
        } else
            reset();
    }
    void copy_allocator(const char_allocator& from, std::true_type) {al = from;}
    void copy_allocator(const char_allocator&, std::false_type) {}
    void move_allocator(char_allocator&& from, std::true_type) {al = std::move(from);}
    void move_allocator(char_allocator&&, std::false_type) {}
    void swap_allocator(char_allocator& from, std::true_type) {using std::swap; swap(al, from);}
    void swap_allocator(char_allocator&, std::false_type) {}
public:
    typedef interface element_type;
    typedef interface* pointer;

    value_ptr() : al(), implementation(nullptr) {dynamic_size()=0;}
    value_ptr(const given_allocator& a) : al(a), implementation(nullptr) {dynamic_size()=0;}
    value_ptr(const value_ptr& rhs) : al(rhs.al), implementation(nullptr) {
        if (rhs.implementation == rhs.get_buf())
            implementation = rhs.implementation->construct(al, get_buf(), use_copy());
        else if (rhs.implementation) {
            dynamic_size() = 0;
            implementation = rhs.implementation->assign(al, nullptr, dynamic_size(), get_buf(), sizeof(buffer), use_copy());
        }
    }
    value_ptr(value_ptr&& rhs) : al(rhs.al), implementation(nullptr) {
        if (rhs.implementation == rhs.get_buf())
            implementation = rhs.implementation->construct(al, get_buf(), use_move());
        else {
            implementation = rhs.implementation;
            dynamic_size() = rhs.dynamic_size();
            rhs.implementation = nullptr;
            rhs.dynamic_size() = 0;
        }
    }
    template<size_t other_give_buf_size, class otheralloc>
    value_ptr(const value_ptr<interface, other_give_buf_size,otheralloc>& rhs) : al(rhs.al), implementation(nullptr) {
        if (rhs.implementation) {
            if (rhs.implementation->get_size() <= sizeof(buffer)) 
                implementation = rhs.implementation->construct(al, get_buf(), use_copy());
            else {
                dynamic_size() = 0;
                implementation = rhs.implementation->assign(al, nullptr, dynamic_size(), get_buf(), sizeof(buffer), use_copy());
            }
        }
    }
    template<size_t other_give_buf_size, class otheralloc>
    value_ptr(value_ptr<interface, other_give_buf_size,otheralloc>&& rhs) : al(rhs.al), implementation(nullptr) {
        if (rhs.implementation) {
            if (rhs.implementation != rhs.get_buf()) {
                implementation = rhs.implementation;
                dynamic_size() = rhs.dynamic_size();
                rhs.implementation = nullptr;
                rhs.dynamic_size() = 0;
            } else if (rhs.implementation->get_size() <= sizeof(buffer)) {
                implementation = rhs.implementation->construct(al, get_buf(), use_move());
            } else {
                dynamic_size() = 0;
                implementation = rhs.implementation->assign(al, nullptr, dynamic_size(), get_buf(), sizeof(buffer), use_move());
            }
        }
    }
    template<class T, 
        class rrt=typename std::remove_const<typename std::remove_reference<T>::type>::type, 
        class allowed=typename std::enable_if<std::is_base_of<interface, rrt>::value, void*>::type>
    explicit value_ptr(T&& v) : al(), implementation(nullptr)
    {
        typedef detail::dispatch_implementation<rrt,interface,char_allocator> impl_type;
        if (sizeof(impl_type)<=sizeof(buffer)) {
            al.construct((impl_type*)get_buf(), std::forward<T>(v));
            implementation = (impl_type*)get_buf();
        } else {
            dynamic_size() = 0;
            auto raw = safe_alloc<impl_type>(al, sizeof(impl_type));
            al.construct(raw.get(), std::forward<T>(v));
            implementation = raw.release();
        }
    }
    template<class T, 
        class rrt=typename std::remove_const<typename std::remove_reference<T>::type>::type, 
        class allowed=typename std::enable_if<std::is_base_of<interface, rrt>::value, void*>::type>
    value_ptr(T&& v, const given_allocator& a) : al(a), implementation(nullptr)
    {
        typedef detail::dispatch_implementation<rrt,interface,char_allocator> impl_type;
        if (sizeof(impl_type)<=sizeof(buffer)) {
            al.construct((impl_type*)get_buf(), std::forward<T>(v));
            implementation = (impl_type*)get_buf();
        } else {
            dynamic_size() = 0;
            auto raw = safe_alloc<impl_type>(al, sizeof(impl_type));
            al.construct(raw.get(), std::forward<T>(v));
            implementation = raw.release();
        }
    }

    ~value_ptr() {reset();}
    value_ptr& operator=(const value_ptr& rhs) {
        copy_allocator(rhs.al, typename std::allocator_traits<char_allocator>::propagate_on_container_copy_assignment());
        if (rhs.implementation) {
            dispatch_interface* old = implementation;
            implementation = nullptr;
            implementation = rhs.implementation->assign(al, old, dynamic_size(), get_buf(), sizeof(buffer), use_copy());
        } else
            reset();
        return *this;
    }
    value_ptr& operator=(value_ptr&& rhs) {
        move_allocator(std::move(rhs.al), typename std::allocator_traits<char_allocator>::propagate_on_container_move_assignment());
        move_noalloc_(std::move(rhs));
        return *this;
    }
    value_ptr& operator=(std::nullptr_t) {
        reset();
        return *this;
    }
    //TODO implement operator=(const value_ptr<interface,other_give_buf_size,otheralloc>&)
    //TODO implement operator=(value_ptr<interface,other_give_buf_size,otheralloc>&&)
    //TODO implement operator=(const T& v)
    //TODO implement operator=(T&& v)
    friend void swap(value_ptr& lhs, value_ptr& rhs) {
        if (lhs.implementation!=lhs.get_buf() && rhs.implementation!=rhs.get_buf()) {
            lhs.swap_allocator(rhs.al, typename std::allocator_traits<char_allocator>::propagate_on_container_swap());
            std::swap(lhs.implementation,rhs.implementation);
            std::swap(lhs.dynamic_size(), rhs.dynamic_size());
        } else {
            value_ptr temp(std::move(lhs));
            lhs = std::move(rhs);
            rhs = std::move(temp);
        }
    }
    
    void reset()
    {
        if (implementation) {
            implementation->~dispatch_interface();
            if (implementation != get_buf())
                al.deallocate(reinterpret_cast<char*>(implementation), dynamic_size());
            dynamic_size() = 0;
            implementation = nullptr;
#ifdef _DEBUG
            memset(&buffer, sizeof(buffer), 0);
#endif
        }
    }
    void emplace(std::nullptr_t) {reset();}
    template<class T, class...Us>
    void emplace(Us...vs) {
        static_assert(std::is_base_of<interface, T>::value, "type T must inhereit from the interface");
        static_assert(std::is_constructible<T,Us...>::value, "type T is not constructable from Us...");
        typedef detail::dispatch_implementation<T,interface,char_allocator> impl_type;

        if (implementation && implementation != get_buf() && dynamic_size() >= sizeof(impl_type)) {
            implementation->~dispatch_interface();
            auto old = reuse_alloc<impl_type>(implementation, al, dynamic_size());
            implementation = nullptr;
            al.construct(old, std::forward<Us>(vs)...);
            implementation = old.commit();
        } else if (sizeof(impl_type)<=sizeof(buffer)) {
            impl_type* target = reinterpret_cast<impl_type*>(get_buf());
            al.construct(target, std::forward<Us>(vs)...);
            implementation = target;
        } else {
            auto raw = safe_alloc<impl_type>(al, sizeof(impl_type));
            al.construct(raw, std::forward<Us>(vs)...);
            implementation = raw.commit();
        }
    }
    template<class T>
    typename std::enable_if<std::is_base_of<interface, T>::value,void>::type emplace(T&& t) {
        emplace<T>(std::move(t));
    }
    template<class T>
    typename std::enable_if<std::is_base_of<interface, T>::value,void>::type emplace(const T& t) {
        emplace<T>(t);
    }
    
    operator interface*() {return implementation ? implementation->get() : nullptr;}
    operator const interface*() const {return implementation ? implementation->get() : nullptr;}
    interface* get() {return implementation ? implementation->get() : nullptr;}
    const interface* get() const {return implementation ? implementation->get() : nullptr;}
    interface* operator->() {return implementation->get();}
    const interface* operator->() const {implementation->get();}
    interface& operator*() {return *(implementation->get());}
    const interface& operator*() const {*(implementation->get());}

    friend bool operator==(const value_ptr& left, const value_ptr& right) {
        if (left.implementation && right.implementation) //if both have data
            return left.implementation->equals(right.implementation); //try to compare them
        else 
            return left.implementation == right.implementation; //equal if both null, otherwise one is null and one isn't
    }
    friend bool operator!=(const value_ptr& left, const value_ptr& right) 
    {return !(left==right);}
};
}//namespace mpd















#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::pair<long long,long long>& val) 
{return out << val.first<<','<<val.second<<'\n';}

struct main_interface {
    virtual ~main_interface() {}
    virtual std::ostream& write(std::ostream&) const =0;
};
std::ostream& operator<<(std::ostream& out, const main_interface& val) 
{return val.write(out);}

template<class T>
struct main_implementation : public main_interface {
    T data;
    main_implementation() :data() {std::cout << "  impl()\n";}
    main_implementation(const T& t) :data(t) {std::cout << "  impl(const T)\n";}
    main_implementation(T&& t) :data(std::move(t)) {std::cout << "  impl(T&&)\n";}
    main_implementation(const main_implementation& rhs) :data(rhs.data) {std::cout << "  impl(const impl&)\n";}
    main_implementation(main_implementation&& rhs) :data(std::move(rhs.data)) {std::cout << "  impl(impl&&)\n";}
    ~main_implementation() {std::cout<<"  ~impl()\n";}
    std::ostream& write(std::ostream& out) const {return out << "  "<< data << "\n";}
    //bool operator==(const implementation& rhs) const {return data==rhs.data;}
};

template<>
struct main_implementation<void> : public main_interface {
    main_implementation() {std::cout << "  impl()\n";}
    main_implementation(const main_implementation& rhs) =delete;
    main_implementation(main_implementation&& rhs) =delete;
    main_implementation&operator=(const main_implementation& rhs) =delete;
    main_implementation&operator=(main_implementation&& rhs) =delete;
    ~main_implementation() {std::cout<<"  ~impl()\n";}
    std::ostream& write(std::ostream& out) const {return out<<"  <VOID>\n";}
    //bool operator==(const implementation& rhs) const {return data==rhs.data;}
};
int main() {
    typedef std::pair<long long,long long> large;
    using mpd::value_ptr;
    static const int buf_size = 16;
    static_assert(sizeof(main_implementation<char>)<sizeof(main_implementation<large>), "impls are same size!");
    static_assert(sizeof(main_implementation<char>)<=buf_size, "buf_size is too small");
    static_assert(sizeof(main_implementation<large>)>buf_size, "buf_size is too big");


    std::cout<<"{\n";
    {
    std::cout<<"const main_implementation<char> a('c');\n";
    const main_implementation<char> a('c');
    std::cout<<"const main_implementation<large> b(large(3,5));\n";
    const main_implementation<large> b(large(3,5));
    
    std::cout<<"const value_ptr<main_interface, buf_size> ptr0;\n";
    const value_ptr<main_interface, buf_size> ptr0;
    std::cout<<"const value_ptr<main_interface, buf_size> ptr1(a);\n";
    const value_ptr<main_interface, buf_size> ptr1(a);
    std::cout<<"const value_ptr<main_interface, buf_size> ptr2(b);\n";
    const value_ptr<main_interface, buf_size> ptr2(b);
    std::cout<<"const value_ptr<main_interface, buf_size> ptr3(ptr0);\n";
    const value_ptr<main_interface, buf_size> ptr3(ptr0);
    std::cout<<"const value_ptr<main_interface, buf_size> ptr4(ptr1);\n";
    const value_ptr<main_interface, buf_size> ptr4(ptr1);
    std::cout<<"const value_ptr<main_interface, buf_size> ptr5(ptr2);\n";
    const value_ptr<main_interface, buf_size> ptr5(ptr2);
    
    std::cout<<"value_ptr<main_interface, buf_size> ptr6 = value_ptr<main_interface, buf_size>{ptr0};\n";
    value_ptr<main_interface, buf_size> ptr6 = value_ptr<main_interface, buf_size>{ptr0};
    std::cout<<"value_ptr<main_interface, buf_size> ptr7 = value_ptr<main_interface, buf_size>{ptr1};\n";
    value_ptr<main_interface, buf_size> ptr7 = value_ptr<main_interface, buf_size>{ptr1};
    std::cout<<"value_ptr<main_interface, buf_size> ptr8 = value_ptr<main_interface, buf_size>{ptr2};\n";
    value_ptr<main_interface, buf_size> ptr8 = value_ptr<main_interface, buf_size>{ptr2};
    
    std::cout<<"value_ptr<main_interface, buf_size> t;\n";
    value_ptr<main_interface, buf_size> t;
    std::cout<<"t = ptr0;\n";
    t = ptr0;
    std::cout<<"t = ptr1;\n";
    t = ptr1;
    std::cout<<"t = ptr2;\n";
    t = ptr2;  //WTF does this change ptr8?
    std::cout<<"t = ptr1;\n";
    t = ptr1;
    std::cout<<"t = ptr0;\n";
    t = ptr0;
    std::cout<<"t = ptr2;\n";
    t = ptr2;
    std::cout<<"t = ptr0;\n";
    t = ptr0;
    
    std::cout<<"t = value_ptr<main_interface, buf_size>{ptr0};\n";
    t = value_ptr<main_interface, buf_size>{ptr0};
    std::cout<<"t = value_ptr<main_interface, buf_size>{ptr1};\n";
    t = value_ptr<main_interface, buf_size>{ptr1};
    std::cout<<"t = value_ptr<main_interface, buf_size>{ptr2};\n";
    t = value_ptr<main_interface, buf_size>{ptr2};
    
    std::cout<<"t = nullptr;\n";
    t = nullptr;
    
    std::cout<<"swap(ptr6, ptr7);\n";
    swap(ptr6, ptr7);
    std::cout<<"swap(ptr7, ptr8);\n";
    swap(ptr7, ptr8);
    std::cout<<"swap(ptr8, ptr6);\n";
    swap(ptr8, ptr6);
    std::cout<<"swap(ptr8, ptr7);\n";
    swap(ptr8, ptr7);
    std::cout<<"swap(ptr7, ptr6);\n";
    swap(ptr7, ptr6);
    std::cout<<"swap(ptr8, ptr6);\n";
    swap(ptr8, ptr6);    
    
    std::cout<<"ptr6->write(std::cout);\n";
    ptr6->write(std::cout);
    std::cout<<"std::cout << *ptr8;\n";
    std::cout << *ptr8;
    
    std::cout<<"}\n";
    }

    return 0;
}