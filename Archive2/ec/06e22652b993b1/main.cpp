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
    friend bool operator!=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr!=r.ptr); return l.index!=r.index;} 
    friend bool operator<(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr!=r.ptr); return l.index<r.index;} 
    friend bool operator>(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr!=r.ptr); return l.index>r.index;} 
    friend bool operator<=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr!=r.ptr); return l.index<=r.index;} 
    friend bool operator>=(const reference_iterator& l, const reference_iterator& r) {assert(l.ptr!=r.ptr); return l.index>=r.index;} 
};

template<typename T, class A=std::allocator<T>>
class bi_vec : protected A
{    
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;
    typedef typename A::pointer iterator;
    typedef typename A::const_pointer const_iterator;    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    bi_vec() :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {}
    bi_vec(const bi_vec& r) :buffer(nullptr), first(nullptr), last(nullptr), endbuf(nullptr) {_insert(buffer, r.first, r.last);}
    bi_vec(bi_vec&& r) :buffer(r.buffer), first(r.first), last(r.last), endbuf(r.endbuf) {r.buffer=nullptr; r.first=nullptr; r.last=nullptr; r.endbuf=nullptr;}
    ~bi_vec() {_erase(first,last); allocator_type::deallocate(buffer, endbuf-buffer);}

    bi_vec& operator=(const bi_vec& r) {_erase(first, last); _insert(buffer, r.first, r.last); return *this;}
    bi_vec& operator=(bi_vec&& r) {_erase(first, last); _insert(buffer, std::make_move_iterator(r.first), std::make_move_iterator(r.last)); return *this;}
    bool operator==(const bi_vec& r) const {return size()==r.size() && std::equal(first, last, r.first);}
    bool operator!=(const bi_vec& r) const {return !operator==(r);}
    bool operator<(const bi_vec& r) const {return std::lexicographical_compare(first, last, r.first, r.last, std::less<value_type>());}
    bool operator>(const bi_vec& r) const {return std::lexicographical_compare(first, last, r.first, r.last, std::greater<value_type>());}
    bool operator<=(const bi_vec& r) const {return !operator>(r);}
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
    reference back() {assert(first!=last); return *last;}
    const_reference back() const {assert(first!=last); return *last;}
    template<class ...Args>
    void emplace_front(Args...args) {_emplace(first, std::forward<Args>(args)...);}
    template<class ...Args>
    void emplace_back(Args...args) {_emplace(last, std::forward<Args>(args)...);}
    void push_front(const reference v) {_emplace(first, v);}
    void push_front(value_type&& v) {_emplace(first, std::move(v));}
    void push_back(const reference v) {_emplace(last, v);}
    void push_back(value_type&& v) {_emplace(last, std::move(v));}
    void pop_front() {assert(first!=last); erase(last-1, last);}
    void pop_back() {assert(first!=last); erase(first, first+1);}
    reference operator[](size_type i) {assert(first+i<last); return first[i];}
    const_reference operator[](size_type i) const {assert(first+i<last); return first[i];}
    reference at(size_type i) {if (i<0 || i>=static_cast<size_type>(last-first)) throw std::out_of_range("out of range"); return first[i];}
    const_reference at(size_type i) const {if (i<0 || i>=static_cast<size_type>(last-first)) throw std::out_of_range("out of range"); return first[i];}

    template<class ...Args>
    iterator emplace(const_iterator l, Args... args) {assert(_valid(l)); return _emplace(l, std::forward<Args>(args)...);}
    iterator insert(const_iterator l, const reference v) {assert(_valid(l)); return _emplace(l, v);}
    iterator insert(const_iterator l, value_type&& v) {assert(_valid(l)); return _emplace(l, std::move(v));}
    iterator insert(const_iterator l, size_type c, reference v) {assert(_valid(l)); return _insert(l, reference_iterator<value_type>(v, 0), reference_iterator<value_type>(v, c));}
    template<class iter>
    iterator insert(const_iterator loc, iter f, iter l) {assert(_valid(loc)); return _insert(loc, f, l);}
    iterator insert(const_iterator l, std::initializer_list<value_type> e) {assert(_valid(l)); return _insert(l, e.begin(), e.end());}
    iterator erase(const_iterator l) {assert(_valid(l)); return _erase(l, l+1);}
    iterator erase(const_iterator f, const_iterator l) {assert(_valid(f)); assert(_valid(l)); assert(f<l); return _erase(f, l);}
    void clear() {_erase(first, last);}
    template<class iter>
    void assign(iter f, iter l) {_erase(first, last); _insert(buffer, f, l);}
    void assign(std::initializer_list<value_type> e) {_erase(first, last); _insert(buffer, e.begin(), e.end());}
    void assign(size_type c, const reference v) {_erase(first, last); _insert(buffer, reference_iterator<value_type>(v, 0), reference_iterator<value_type>(v, c));}
    void reserve(size_type prebuffer, size_type postbuffer) {if (prebuffer>capacity_in_front() || postbuffer>capacity_in_back()) _reallocate(prebuffer,postbuffer);}
    void shrink_to_fit() {_reallocate(0,0);}

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
        if (prebuffer < 8) 
            prebuffer = 8;
        if (postbuffer < 8) 
            postbuffer = 8;
        size_type newtotal = prebuffer + last-first + postbuffer;
        iterator newbuf = allocate(newtotal);
        iterator newend = newbuf + newtotal;

        iterator newfirst = newbuf + prebuffer;
        iterator newlast = newfirst;
        try {
            iterator src;
            for(src=first; src!=last; ++src,++newlast)
                construct(newlast, std::move_if_noexcept(*src));
        } catch(...) {
            while(newlast!=newfirst) 
                destroy(--newlast);
            throw;
        }

        _erase(first, last);
        deallocate(buffer, endbuf-buffer);

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
                size_type insert_offset = loc-first;
                size_type pre = (last-first)/2;
                size_type post = pre;
                if (post < count) 
                    post = count;
                _reallocate(pre, post);
                loc = first+insert_offset;
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
            construct(last, std::forward<Args>(args)...);
            ++last;
            std::rotate(loc, last-1, last);
        } else {
            construct(first-1, std::forward<Args>(args)...);
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
            construct(last, *f);
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
                construct(last, *f);
                ++last;
                ++f;
            }
            std::rotate(loc, oldlast, last);
            return loc;
        } else if (f!=l) {
            iterator oldfirst = first;
            --l;
            do {
                construct(first-1, *l);
                --first;
                --l;
            } while(f!=l);
            return std::rotate(first, oldfirst, loc);
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
            std::rotate(f, l+1, last);
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

template <class T, class A = std::allocator<T> >
void swap(bi_vec<T,A>& l, bi_vec<T,A>& r)
{l.swap(r);}


int main() {
    bi_vec<int> a;

}