#include <iostream>
#include <map>
#include <vector>

template <typename T, bool IS_CLASS>
class Citerator;

// If we are supplied an int, char,... , we must create an iterator around it.
template <typename TYPE>
class Citerator<TYPE, false> : public std::iterator<std::input_iterator_tag, TYPE>
{
public:

    Citerator(TYPE iterator):m_raw_iterator(iterator){}
    Citerator(const Citerator &iterator):m_raw_iterator(iterator.m_raw_iterator){}
    Citerator &operator=(const Citerator &iterator){m_raw_iterator = iterator.m_raw_iterator; return *this;}

    bool operator==(const Citerator &citerator){return m_raw_iterator == citerator.m_raw_iterator;}
    bool operator!=(const Citerator &citerator){return m_raw_iterator != citerator.m_raw_iterator;}

    TYPE &operator*(){return m_raw_iterator;}
    TYPE &operator->(){return m_raw_iterator;}

    Citerator &operator++(){++m_raw_iterator; return *this;}
    Citerator &operator++(int){m_raw_iterator++; return *this;}

    TYPE &get(){return m_raw_iterator;}

private:

    TYPE m_raw_iterator;

};

// If we are provided an iterator, we inherit from it.
template <typename TYPE>
class Citerator<TYPE, true> : public TYPE
{
public:
    using TYPE::TYPE;
    TYPE &get(){return *this;}
};

// The iterator that wraps around both integers and other iterators.
template <typename TYPE, bool IS_CLASS = std::is_class<TYPE>::value>
class Iterator : public Citerator<TYPE, IS_CLASS>
{
public:
    using Citerator<TYPE, IS_CLASS>::Citerator;
};

int main()
{
    Iterator<int> a(0), b(22);

    std::vector<int> ax;
    Iterator<std::vector<int>::iterator> c(ax.begin()), d(ax.end());

    std::map<std::size_t, std::vector<int>> bx;
    Iterator<std::map<std::size_t, std::vector<int>>::iterator> e(bx.begin()), f(bx.end()); // Error occurs here.
}
