#include <iterator>

template <typename Generator>
struct generator_iterator : std::iterator<std::forward_iterator_tag, int> {
    generator_iterator(const Generator &gen, bool end = false) : count(0), gen(gen), lastval(0), is_end(end) {
        if (!end) // FIXED
            advance();
    }
    void advance() {
        if (gen.HasNext()) {
            lastval = gen.Next();
            count += 1;
        } else {
            is_end = true;
        }
    }
    int operator *() {
        return lastval;
    }
    generator_iterator &operator++() {
        advance();
        return *this;
    }
    generator_iterator operator++(int) {
        generator_iterator result = *this;
        advance();
        return result;
    }
    bool operator==(const generator_iterator &rhs) {
        return (is_end && rhs.is_end) ||
               ((is_end == rhs.is_end) && (count == rhs.count)); // FIXED
    }
    bool operator!=(const generator_iterator &rhs) {
        return !(*this == rhs);
    }

    size_t count;
    Generator gen;
    int lastval;
    bool is_end; 
};

#include <limits>
#include <iostream>
struct MyGenerator 
{ 
    int count = 0;

    bool HasNext() {
        return count != std::numeric_limits<int>::max();
    }
    
    int Next() { 
        int v = rand() % 100;
        std::cout << "Using source value " << v << "\n";
        return v;
    }
};

#include <cassert>

int main() { 
    generator_iterator<MyGenerator> first(MyGenerator{});
    
    auto copy1(first);
    auto copy2(copy1);

    assert(first    == copy1);    // no problem
    assert(copy1    == copy2);    // no problem
    assert(*copy1++ == *copy2++); // no problem

    assert(copy1    == copy2);    // no problem? Iterator state identical, but generator already diverged
    assert(*copy1   == *copy2);   // whoops - we can observe the diverged state
}
