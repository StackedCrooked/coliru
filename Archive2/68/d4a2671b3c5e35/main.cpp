#include <iostream>
#include <vector>

template <class M>
struct member_traits;
    
template <class T, class C>
struct member_traits<T C::*>
{
    using class_type = C;
    using return_type = T;
};

template <class Iterator, class C, class M>
struct member_iterator : Iterator
{
public:
    using Iterator::Iterator;
    
    template <class I, class Member>
    member_iterator(I&& begin, Member&& member)
        : std::vector<C>::iterator(std::forward<I>(begin))
        , member(std::forward<Member>(member))
    {
        static_assert(std::is_member_pointer<Member>::value, "Member must be dereferenceable");
    }
    
    typename member_traits<M>::return_type& operator*()
    {
        return (*static_cast<Iterator&>(*this)).*member;
    }
private:
    M member;
};

template <class Member, class Iterator>
auto make_member_iterator(Member&& member, Iterator&& it)
    -> member_iterator<Iterator, typename member_traits<Member>::class_type, std::decay_t<Member>>
{
    return {std::forward<Iterator>(it), std::forward<Member>(member)};
}

struct Record
{
    int field1;
    double field2;
};

int main()
{
    std::vector<Record> v { {1, 1.0}, {2, 2.0}, {3, 3.0} };
    
    for (auto it = make_member_iterator(&Record::field1, v.begin()); it != v.end(); ++it)
    {
        std::cout << *it << " ";
    }
}