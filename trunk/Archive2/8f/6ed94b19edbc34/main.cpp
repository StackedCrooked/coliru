#include <iostream>
#include <list>

template <class T>
class IteratorIterable
{
private:
    T& container;

public:
    typedef typename T::iterator BackendIterator;

public:
    class IteratorIterator
    {
    public:
        IteratorIterator() : it() {}
        IteratorIterator(BackendIterator it) : it(it) {}
        IteratorIterator(const IteratorIterator& other) : it(other.it) {}

        IteratorIterator& operator=(const IteratorIterator& other) { if (&other == this) return *this; it = other.it; return *this; }

        BackendIterator operator*() const { return it; }
        const BackendIterator* operator->() const { return &it; }

        bool operator==(const IteratorIterator& other) { return it == other.it; }
        bool operator !=(const IteratorIterator& other) { return it != other.it; }

         template<typename... Dummy, typename Iter = BackendIterator>
         typename std::enable_if<
            std::is_same<typename std::iterator_traits<Iter>::iterator_category,
                         std::random_access_iterator_tag>::value,
            IteratorIterator>::type
         operator+(size_t n) 
         {
             static_assert(sizeof...(Dummy)==0, "Do not specify template paramters");
             return IteratorIterator(it + n); 
         }

        IteratorIterator& operator++() { ++it; return *this; }
        IteratorIterator operator++(int) { IteratorIterator cpy(*this); ++(*this); return cpy; }

    private:
        BackendIterator it;
    };

public:
    IteratorIterable(T& container) : container(container) {}

    IteratorIterator begin() const { return IteratorIterator(container.begin()); }
    IteratorIterator end() const { return IteratorIterator(container.end()); }
};


template <class T>
IteratorIterable<T> ItIt(T& container)
{
    return IteratorIterable<T>(container);
}

template class IteratorIterable<std::list<int>>;

int main() 
{
    typedef std::list<int> Cont;

    Cont vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    IteratorIterable<Cont> itb(vec);

    IteratorIterable<Cont>::IteratorIterator beg = itb.begin();
    IteratorIterable<Cont>::IteratorIterator it = beg;

    it++;
    //it = beg+1;
}
