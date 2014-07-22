#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>

template<typename Iterator,
         typename Address = decltype(std::addressof(**std::declval<Iterator>()))
         >
class address_iterator : public std::iterator<std::input_iterator_tag, Address>
{
public:
    address_iterator(Iterator i) : i_{std::move(i)} {};

    Address operator*() const {
        return std::addressof(**i_);
    };

    Address operator->() {
        return *this;
    }
    
    address_iterator& operator++() {
        ++i_;
        return *this;
    };
    
    address_iterator operator++(int) {
        auto&& old = *this;
        operator++();
        return old;
    }
    
    bool operator==(address_iterator const& other) const {
        return i_ == other.i_;
    }
    
private:
    Iterator i_;
};

template<typename Iterator>
bool operator!=(address_iterator<Iterator> const& lhs, address_iterator<Iterator> const& rhs) {
    return !(lhs == rhs);
}

template<typename Iterator>
address_iterator<Iterator> make_address_iterator(Iterator i) {
    return i;
}

// Element Class
struct Foo { };

// Take a range of elements, sort them internally by their addresses and print them in order    
template <typename FooIterator>
void print_sorted_addresses(FooIterator beginFoos, FooIterator endFoos) {
    std::vector<const Foo*> elements(make_address_iterator(beginFoos), make_address_iterator(endFoos));
    std::sort(elements.begin(), elements.end());
    for(const auto& e : elements)
        std::cout << &e << std::endl;
}

int main() {
#ifdef UNIQUE
    std::vector<std::unique_ptr<Foo>> foos;
#else
    std::vector<Foo*> foos;
#endif

    for(int i = 0; i < 10; ++i) {
        foos.emplace_back(new Foo());
    }

#ifdef UNIQUE
    std::cout << "from unique_foos:\n";
#else
    std::cout << "from raw_foos:\n";
#endif

    print_sorted_addresses(foos.cbegin(), foos.cend());

    return 0;
}
