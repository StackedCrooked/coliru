#include <iostream>
#include <vector>
#include <tuple>

template<typename T>
class array
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
private:
    iterator head;
    unsigned long elems;
public:
    array()
        : head(nullptr)
        , elems(0) {}
    array(const unsigned long &size)
        : head(size > 0 ? new T[size] : nullptr)
        , elems(size) {}
    array(std::initializer_list<T> il);
    array(const array&);
    ~array() { delete[] head; }

    iterator begin() const { return head; }
    iterator end() const { return head != nullptr ? &head[elems] : nullptr; }
    unsigned long size() const { return elems; }

    array& operator=(const array&);
    T& operator()(const unsigned long&);
};

template<typename T>
array<T>::array(std::initializer_list<T> il)
{
    unsigned long size = il.size();
    head = new T[size];
    iterator pointer = begin();
    for (const T& i : il)
        *pointer++ = i;
}

template<typename T>
array<T>::array(const array<T> &rhs)
{
    head = new T[rhs.size()];
    iterator pointer = begin();
    for (const_iterator i = rhs.begin(); i != rhs.end(); i++)
        *pointer++ = *i;
}

template<typename T>
array<T>& array<T>::operator=(const array<T> &rhs)
{
    if (this != &rhs)
    {
        delete[] head;
        head = new T[rhs.size()];
        iterator pointer = begin();
        for (const_iterator i = rhs.begin(); i != rhs.end(); i++)
            *pointer++ = *i;
    }
    return *this;
}

template<typename T>
T& array<T>::operator()(const unsigned long &index)
{
    if (index < 1 || index > size())
    {
        // Add some error-handling here.
    }
    return head[index - 1];
}

int main()
{
    array<int> test = {1, 2, 3, 4};
    std::cout << test(1) << std:: endl;
    std::cout << test(4) << std::endl;
}
