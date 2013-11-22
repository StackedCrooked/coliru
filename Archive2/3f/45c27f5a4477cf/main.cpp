// STL
#include <iostream>
#include <cassert>
#include <cstddef> // std::size_t
#include <cstring> // std::memset, std::memcpy
#include <utility> // std::move

// Boost
#include <boost/noncopyable.hpp>


template <typename T, std::size_t n>
struct staff : boost::noncopyable
{
    typedef T(buffer_type)[n];
    enum { length = sizeof(T) * n };

    staff()
    {
        std::cout << "staff default constructor ("
            << this << ')' << std::endl;
        std::memset(reinterpret_cast<void*>(&m_buffer_), 0, length);
    }

    staff(const staff& rhs)
    {
        std::cout << "staff copy constructor ("
            << this << ')' << std::endl;
    
        std::memcpy(reinterpret_cast<void*>(&m_buffer_),
                    reinterpret_cast<void*>(const_cast<buffer_type*>(&rhs.m_buffer_)),
                    length);
    }

    ~staff()
    {
        std::cout << "staff destructor (" << this << ')' << std::endl;
    }

    buffer_type m_buffer_;
};

template <
    typename T
  , std::size_t n = 1024
  , template <typename, std::size_t> class Staff = staff
> class A
{
    typedef T data_type;
    enum { size = n };
    typedef Staff<data_type, size> staff_type;
    typedef A<data_type, size, Staff> this_type;

public:

    A() : m_staff_ptr_(new staff_type())
    {
        std::cout << "A default constructor (" << this << ')' << std::endl;
    }

    A(const A& rhs) : m_staff_ptr_(new staff_type(*rhs.m_staff_ptr_))
    {
        std::cout << "A copy constructor (" << this << ')' << std::endl;
    }

    A(A&& rhs)
    {
        std::cout << "A move constructor (" << this << ')' << std::endl;
        assert(rhs.m_staff_ptr_);

        m_staff_ptr_ = rhs.m_staff_ptr_;
        rhs.m_staff_ptr_ = 0;
    }

    ~A()
    {
        std::cout << "A destructor (" << this << ')' << std::endl;
        if (m_staff_ptr_)
            delete m_staff_ptr_;
        m_staff_ptr_ = 0;
    }

    staff_type& get_staff()
    {
        std::cout << "A get_staff() (" << this << ')' << std::endl;
        return *m_staff_ptr_;
    }

    const staff_type& get_staff() const
    {
        std::cout << "A get_staff() const (" << this << ')' << std::endl;
        return *m_staff_ptr_;
    }

    typedef staff_type* this_type::*unspecified_bool_type;

    operator unspecified_bool_type() const
      { return m_staff_ptr_ == 0 ? 0 : &this_type::m_staff_ptr_; }

private:
    staff_type* m_staff_ptr_;    
};

int main()
{
    std::cout << "A<char> a1;" << std::endl;
    A<char> a1;
    std::cout << "&a1.get_staff() = [" << &a1.get_staff() << ']' << std::endl;
    std::cout << "static_cast<bool>(a1) = ["
    << static_cast<bool>(a1) << ']' << std::endl;

    std::cout << std::endl;


    std::cout << "A<char> a2(a1);" << std::endl;
    A<char> a2(a1);

    std::cout << "&a2.get_staff() = [" << &a2.get_staff() << ']' << std::endl;
    std::cout << "static_cast<bool>(a2) = ["
    << static_cast<bool>(a2) << ']' << std::endl;

    std::cout << std::endl;


    std::cout << "A<char> a3(std::move(a1));" << std::endl;
    A<char> a3(std::move(a1));

    std::cout << "&a3.get_staff() = [" << &a3.get_staff() << ']' << std::endl;
    std::cout << "static_cast<bool>(a3) = ["
    << static_cast<bool>(a3) << ']' << std::endl;
    std::cout << "static_cast<bool>(a1) = ["
    << static_cast<bool>(a1) << ']' << std::endl;

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
