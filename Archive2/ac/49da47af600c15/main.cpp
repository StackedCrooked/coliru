//http://stackoverflow.com/questions/24639573/is-there-center-allocation-deque-vector-in-stl-implementations

#include <iterator>
#include <memory>
#include <algorithm>
#include <utility>
#include <deque>
#include <functional>
#include <cassert>

#ifndef _NOEXCEPT
#define _NOEXCEPT    throw ()
#define _NOEXCEPT_OP(x)
#endif

template<class T>
class reference_iterator
{
    T* ptr;
    std::size_t index;
public:
    typedef std::size_t size_type;
    typedef std::size_t difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::random_access_iterator_tag iterator_category;
    
    reference_iterator() : ptr() {}  
    reference_iterator(T& ref, std::size_t index) : ptr(&ref), index(index) {}  

    reference operator*() const {return *ptr;}
    pointer operator->() const {return ptr;}

    reference_iterator& operator++() {++index; return *this;}
    reference_iterator operator++(int) {return reference_iterator(*ptr, index+1);}
    reference_iterator& operator+=(size_type o) {index+=o; return *this;}
    friend reference_iterator operator+(const reference_iterator& it, size_type o) {return reference_iterator(*it, it.index+o);}
    friend reference_iterator operator+(size_type o, const reference_iterator& it) {return reference_iterator(*it, it.index+o);}
    reference_iterator& operator--() {--index; return *this;}
    reference_iterator operator--(int) {--index; return *this;}
    reference_iterator& operator-=(size_type o) {index-=o; return *this;}
    friend reference_iterator operator-(const reference_iterator& it, size_type o) {return reference_iterator(*it, it.index-o);}
    friend difference_type operator-(reference_iterator l, reference_iterator r) {return l.index-r.index;}

    friend bool operator==(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index==r.index;}
    friend bool operator!=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index!=r.index;} 
    friend bool operator<(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index<r.index;} 
    friend bool operator>(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index>r.index;} 
    friend bool operator<=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index<=r.index;} 
    friend bool operator>=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr==r.ptr); return l.index>=r.index;} 
};
template<class T>
reference_iterator<T> make_ref_iter(T& t, std::size_t index) {return reference_iterator<T>(t, index);}

template<typename T, class A=std::allocator<T>>
class bi_vec : protected A
{    
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::pointer pointer;
    typedef typename A::const_pointer const_pointer;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer iterator;
    typedef typename A::const_pointer const_iterator;    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    bi_vec() :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {}
    bi_vec(const bi_vec& r) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(buffer, r.first, r.last);}
    bi_vec(bi_vec&& r) :buffer(r.buffer), first(r.first), last(r.last), endbuf(r.endbuf) {r.buffer=nullptr; r.first=nullptr; r.last=nullptr; r.endbuf=nullptr;}
    explicit bi_vec(allocator_type a) : allocator_type(std::move(a)), buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {}
    bi_vec(const bi_vec& r, allocator_type a) :allocator_type(std::move(a)), buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(buffer, r.first, r.last);}
    bi_vec(bi_vec&& r, allocator_type a) :allocator_type(std::move(a)), buffer(r.buffer), first(r.first), last(r.last), endbuf(r.endbuf) {r.buffer=nullptr; r.first=nullptr; r.last=nullptr; r.endbuf=nullptr;}
    explicit bi_vec(size_type n) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {inplacefactory f; _insert(first, make_ref_iter(f,0), make_ref_iter(f, n));}
    bi_vec(size_type n, const_reference r) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(first, make_ref_iter(r,0), make_ref_iter(r, n));}
    bi_vec(size_type n, const_reference r, allocator_type a) :allocator_type(std::move(a)), buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(first, make_ref_iter(r,0), make_ref_iter(r, n));}
    template<class InIter, class enabled=typename std::enable_if<!std::is_integral<InIter>::value>::type> 
    bi_vec(InIter f, InIter l) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(first, f, l);}
    bi_vec(std::initializer_list<value_type> r) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(first, r.begin(), r.end());}    
    ~bi_vec() {_erase(first,last); allocator_type::deallocate(buffer, endbuf-buffer);}

    bi_vec& operator=(const bi_vec& r) {_erase(first, last); _insert(buffer, r.first, r.last); return *this;}
    bi_vec& operator=(bi_vec&& r) {_erase(first, last); _insert(buffer, std::make_move_iterator(r.first), std::make_move_iterator(r.last)); return *this;}
    bi_vec& operator=(std::initializer_list<value_type> r) {_erase(first, last); _insert(buffer, r.begin(), r.end()); return *this;}
    
    bool operator==(const bi_vec& r) const {return size()==r.size() && std::equal(first, last, r.first);}
    bool operator!=(const bi_vec& r) const {return !operator==(r);}
    bool operator<(const bi_vec& r) const {return std::lexicographical_compare(first, last, r.first, r.last, std::less<value_type>());}
    bool operator<=(const bi_vec& r) const {return std::lexicographical_compare(first, last, r.first, r.last, std::less_equal<value_type>());}
    bool operator>(const bi_vec& r) const {return !operator<=(r);}
    bool operator>=(const bi_vec& r) const {return !operator<(r);}

    iterator begin() {return first;}
    const_iterator begin() const {return first;}
    const_iterator cbegin() const {return first;}
    iterator end() {return last;}
    const_iterator end() const {return last;}
    const_iterator cend() const {return last;}
    reverse_iterator rbegin() {return reverse_iterator(last);}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(last);}
    const_reverse_iterator crbegin() const {return const_reverse_iterator(last);}
    reverse_iterator rend() {return reverse_iterator(first);}
    const_reverse_iterator rend() const {return const_reverse_iterator(first);}
    const_reverse_iterator crend() const {return const_reverse_iterator(first);}

    reference front() {assert(first!=last); return *first;}
    const_reference front() const {assert(first!=last); return *first;}
    reference back() {assert(first!=last); return *(last-1);}
    const_reference back() const {assert(first!=last); return *(last-1);}
    template<class ...Args>
    void emplace_front(Args...args) {_emplace(first, std::forward<Args>(args)...);}
    template<class ...Args>
    void emplace_back(Args...args) {_emplace(last, std::forward<Args>(args)...);}
    void push_front(const_reference v) {_emplace(first, v);}
    void push_front(value_type&& v) {_emplace(first, std::move(v));}
    void push_back(const_reference v) {_emplace(last, v);}
    void push_back(value_type&& v) {_emplace(last, std::move(v));}
    void pop_front() {assert(first!=last); erase(last-1, last);}
    void pop_back() {assert(first!=last); erase(first, first+1);}
    reference operator[](size_type i) {assert(first+i<last); return first[i];}
    const_reference operator[](size_type i) const {assert(first+i<last); return first[i];}
    reference at(size_type i) {if (i<0 || i>=static_cast<size_type>(last-first)) throw std::out_of_range("out of range"); return first[i];}
    const_reference at(size_type i) const {if (i<0 || i>=static_cast<size_type>(last-first)) throw std::out_of_range("out of range"); return first[i];}

    //TODO ADD RESIZE
    template<class ...Args> iterator emplace(const_iterator l, Args... args) {assert(_valid(l)); return _emplace(l, std::forward<Args>(args)...);}
    iterator insert(const_iterator l, const_reference v) {assert(_valid(l)); return _emplace(l, v);}
    iterator insert(const_iterator l, value_type&& v) {assert(_valid(l)); return _emplace(l, std::move(v));}
    iterator insert(const_iterator l, size_type c, const_reference v) {assert(_valid(l)); return _insert(l, make_ref_iter(v, 0), make_ref_iter(v, c));}
    template<class InIter, class enabled=typename std::enable_if<!std::is_integral<InIter>::value>::type> 
    iterator insert(const_iterator loc, InIter f, InIter l) {assert(_valid(loc)); return _insert(loc, f, l);}
    iterator insert(const_iterator l, std::initializer_list<value_type> e) {assert(_valid(l)); return _insert(l, e.begin(), e.end());}
    iterator erase(const_iterator l) {assert(_valid(l)); return _erase(l, l+1);}
    iterator erase(const_iterator f, const_iterator l) {assert(_valid(f)); assert(_valid(l)); assert(f<l); return _erase(f, l);}
    void clear() {_erase(first, last);}
    template<class InIter, class enabled=typename std::enable_if<!std::is_integral<InIter>::value>::type> 
    void assign(InIter f, InIter l) {_erase(first, last); _insert(first, f, l);}
    void assign(std::initializer_list<value_type> e) {_erase(first, last); _insert(first, e.begin(), e.end());}
    void assign(size_type c, const_reference v) {_erase(first, last); _insert(first, make_ref_iter(v, 0), make_ref_iter(v, c));}
    void reserve(size_type prebuffer, size_type postbuffer) {if (prebuffer>capacity_in_front() || postbuffer>capacity_in_back()) _reallocate(prebuffer,postbuffer);}
    void shrink_to_fit() {_reallocate(0,0);}
    void resize_back(size_type count) {if (count>=size()) {inplacefactory f; _insert(last, make_ref_iter(f, 0), make_ref_iter(f,count-(last-first)));} else _erase(first+count,last); }
    void resize_back(size_type count, const_reference r) {if (count>=size()) {_insert(last, make_ref_iter(r, 0), make_ref_iter(r,count-(last-first)));} else _erase(first+count,last); }
    void resize_front(size_type count) {if (count>=size()) {inplacefactory f; _insert(first, make_ref_iter(f, 0), make_ref_iter(f,count-(last-first)));} else _erase(first, last-count); }
    void resize_front(size_type count, const_reference r) {if (count>=size()) {_insert(last, make_ref_iter(r, 0), make_ref_iter(r,count-(last-first)));} else _erase(first, last-count); }
    pointer data() {return first;}
    const_pointer data() const {return first;}

    void swap(bi_vec& r) {_swap(r);}
    size_type size() const {return last-first;}
    size_type capacity_in_back() const {return endbuf-last;}
    size_type capacity_in_front() const {return first-buffer;}
    size_type max_size() const {return allocator_type::max_size();}
    bool empty() const {return first==last;}

    A get_allocator() {return *this;}
private:
    iterator buffer;
    iterator first;
    iterator last;
    iterator endbuf;
    
    struct inplacefactory {};

    template<class...Args>
    void _construct(iterator loc, Args...args) {allocator_type::construct(loc, std::forward<Args>(args)...);}
    void _construct(iterator loc, const inplacefactory&) {allocator_type::construct(loc);}
    void _construct(iterator loc, inplacefactory&) {allocator_type::construct(loc);}
    void _construct(iterator loc, inplacefactory&&) {allocator_type::construct(loc);}
    
    bool _valid(const_iterator it) {
        return it>=first && it<=last;
    }
    void _swap(bi_vec& r) {
        std::swap(buffer, r.buffer);
        std::swap(first, r.first);
        std::swap(last, r.last);
        std::swap(endbuf, r.endbuf);
    }
    void _reallocate(size_type prebuffer, size_type postbuffer)
    {
        if (first!=last || prebuffer>0 || postbuffer>0) 
        {
            if (prebuffer < 4) 
                prebuffer = 4;
            if (postbuffer < 4) 
                postbuffer = 4;
        }
        size_type newtotal = prebuffer + last-first + postbuffer;
        iterator newbuf = newtotal ? allocator_type::allocate(newtotal) : nullptr;
        iterator newend = newbuf + newtotal;

        iterator newfirst = newbuf + prebuffer;
        iterator newlast = newfirst;
        try {
            iterator src;
            for(src=first; src!=last; ++src,++newlast)
                _construct(newlast, std::move_if_noexcept(*src));
        } catch(...) {
            while(newlast!=newfirst) 
                allocator_type::destroy(--newlast);
            throw;
        }

        _erase(first, last);
        allocator_type::deallocate(buffer, endbuf-buffer);

        buffer = newbuf;
        first = newfirst;
        last = newlast;
        endbuf = newend;
    }
    bool _reserve(iterator& loc, size_t count) //returns true for pushback, false for pushfront
    {
        iterator middle = first + (last-first)/2;
        if (loc < middle) 
        {
            if (static_cast<size_t>(first-buffer) < count)
            {
                size_type insert_offset = loc-first;
                size_type pre = (last-first)/2;
                size_type post = pre;
                if (pre < count) 
                    pre = count;
                _reallocate(pre, post);
                loc = first+insert_offset;
            }
            return false;
        } 
        else 
        {
            if (static_cast<size_t>(endbuf-last) < count)
            {
                if (first==last && static_cast<size_t>(endbuf-buffer) >= count) {
                    first = buffer + (endbuf-buffer)/2 - count/2;
                    loc = last = first;
                } else {
                    size_type insert_offset = loc-first;
                    size_type pre = (last-first)/2;
                    size_type post = pre;
                    if (post < count) 
                        post = count;
                    _reallocate(pre, post);
                    loc = first+insert_offset;
                }
            }
            return true;
        }
    }

    template<class ...Args>
    iterator _emplace(const_iterator loc_, Args... args) 
    {
        iterator loc = const_cast<iterator>(loc_);
        bool dopushback = _reserve(loc, 1);
        if (dopushback) {
            _construct(last, std::forward<Args>(args)...);
            ++last;
            std::rotate(loc, last-1, last);
        } else {
            _construct(first-1, std::forward<Args>(args)...);
            --first;
            std::rotate(first, first+1, loc);
        }
        return loc;
    }
    template<class outit>
    iterator _insert(const_iterator loc, outit f, outit l) 
    {return _insert(loc, f, l, typename std::iterator_traits<outit>::iterator_category{});}
    template<class outit>
    iterator _insert(const_iterator loc_, outit f, outit l, std::input_iterator_tag) 
    {
        iterator loc = const_cast<iterator>(loc_);
        size_type old_count = last-first;
        while(last!=endbuf && f!=l) {
            _construct(last, *f);
            ++last;
            ++f;
        }
        if (f != l) {
            std::deque<value_type,allocator_type> t(f,l);
            _reserve(loc, t.size());
            _insert(last, std::make_move_iterator(t.begin()), std::make_move_iterator(t.end()), std::random_access_iterator_tag{});
        }
        std::rotate(loc, first+old_count, last);
        return loc;
    }
    template<class outit>
    iterator _insert(const_iterator loc_, outit f, outit l, std::bidirectional_iterator_tag) 
    {
        iterator loc = const_cast<iterator>(loc_);
        size_type num_insert = std::distance(f,l);
        bool dopushback = _reserve(loc, num_insert);
        if (dopushback) {
            iterator oldlast = last;
            while(f!=l) {
                _construct(last, *f);
                ++last;
                ++f;
            }
            std::rotate(loc, oldlast, last);
            return loc;
        } else if (f!=l) {
            iterator oldfirst = first;
            do {
                --l;
                _construct(first-1, *l);
                --first;
            } while(f!=l);
            std::rotate(first, oldfirst, loc);
        }
        return loc;
    }
    iterator _erase(const_iterator f_, const_iterator l_) 
    {
        iterator f = const_cast<iterator>(f_);
        iterator l = const_cast<iterator>(l_);
        size_type remainleft = f-first;
        size_type remainright = last-l;
        if (remainleft > remainright) {
            std::rotate(f, l, last);
            iterator newlast = last - (l-f);
            while(last != newlast)
                allocator_type::destroy(--last);
            return f;
        } else {
            std::rotate(first, f, l);
            iterator newfirst = first + (l-f);
            while(first != newfirst)
                allocator_type::destroy(first++);
            return l;
        }
    }
};

template <class T, class A>
void swap(bi_vec<T,A>& l, bi_vec<T,A>& r)
{l.swap(r);}


















#include <iostream>

template class bi_vec<int>; //fully instantiated!  HOORAY!

#define assert_throw(X, E) try { X; assert((X,false)); } catch(const E&) {}
#define assert_throw_any(X) try { X; assert((X,false)); } catch(...) {}

int main() {
    bi_vec<int> a;
    bi_vec<int> b(4);
    bi_vec<int> c(4, 5);
    bi_vec<int> d(c.begin()+1, c.end());
    bi_vec<int> e = b;
    bi_vec<int> f = std::move(b);
    bi_vec<int> g = {7, 6, 5};
    b.clear();

    *(c.begin()) = 1;
    assert(c[0] == 1);
    *(c.end()-1) = 2;
    assert(c[3] == 2);
    *(c.rbegin()) = 3;
    assert(c[3] == 3);
    *(c.rend()-1) = 4;
    assert(c[0] == 4);

    assert(*(c.cbegin()) == 4);
    assert(*(c.cend()-1) == 3);
    assert(*(c.crbegin()) == 3);
    assert(*(c.crend()-1) == 4);

    assert(c.size() == 4);
    assert(c.max_size() > 99999);
    assert(a.empty());
    assert(a.capacity_in_back() == 0);
    assert(a.capacity_in_front() == 0);
    a.reserve(10, 12);
    assert(a.capacity_in_front() == 10);
    assert(a.capacity_in_back() == 12);
    a.shrink_to_fit();
    assert(a.capacity_in_back()==0);
    assert(a.capacity_in_front()==0);


    c.resize_back(5);
    assert(c.size() == 5);
    c.resize_back(4);
    assert(c.size() == 4);

    c.resize_front(5);
    assert(c.size() == 5);
    c.resize_front(4);
    assert(c.size() == 4);
    assert(c.front() == 4);
    assert(c.back() == 3);
    assert(c.data()[0] == 4);
    assert(c.at(0)==4);
    assert(c.at(3)==3);
    assert_throw(c.at(4),std::out_of_range);

    c.push_back(5);
    assert(c.size() == 5);
    assert(c[4] == 5);
    c.pop_back();
    assert(c.size() == 4);
    d.assign(c.begin(), c.end());
    assert(c == d);
    assert(d.size() == c.size());
    d.assign(3, 6);
    assert(d.size() == 3);
    assert(d[0] == 6);
    d.assign({6, 6, 6});
    assert(d.size() == 3);
    assert(d[0] == 6);
   
    d.insert(d.begin()+1, 2);
    assert(d[1] == 2);
    d.insert(d.begin()+1, 2, 3);
    assert(d[0] == 6);
    assert(d[1] == 3);
    assert(d[2] == 3);
    assert(d[3] == 2);
    d.insert(d.begin(), e.begin(), e.end());
    assert(d[0] == 0);
    assert(d[3] == 0);
    assert(d[4] == 6);
    d.insert(d.begin(), {10, 11});
    assert(d[0] == 10);
    assert(d[1] == 11);
    assert(d[2] == 0);
    assert(d[6] == 6);

    d.erase(d.begin()+1);
    assert(d[0] == 10);
    assert(d[1] == 0);
    assert(d[5] == 6);
    d.erase(d.begin()+1, d.end()-1);
    assert(d.size() == 2);
    
    d.emplace_back(7);
    assert(d.size() == 3);
    assert(d[2] == 7);
    d.emplace(d.begin()+1, 9);
    assert(d[1] == 9);

    d.swap(e);
    assert(d.size() == 4);
    d.clear();
    assert(d.size() == 0);

    std::allocator<int> z = d.get_allocator();

    assert(f != b);
    assert(f==b == false);
    assert(f<b == false);
    assert(f>b);
    assert(f<=b == false);
    assert(f>=b);
    
    std::cout << "passed all tests";

    return 0;
}