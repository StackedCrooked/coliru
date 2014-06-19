#include <iostream>
#include <vector>

template<typename T, typename A = std::allocator<T>>
struct vector_wrap
{
    using iterator = typename std::vector<T, A>::const_iterator;
    using const_iterator = typename std::vector<T, A>::const_iterator;
    using size_type = typename std::vector<T, A>::size_type;
    
    vector_wrap(std::vector<T, A>& vec)
    : vec_(&vec)
    {}
    
    void push_back(T const& value) { vec_->push_back(value); }
    void push_back(T&& value) { vec_->push_back(std::move(value)); }
    size_type size() { return vec_->size(); }
    iterator begin() const { return vec_->cbegin(); }
    iterator end() const { return vec_->cend(); }
    
private:
    std::vector<T, A> *vec_;
};

template<typename T, typename A>
vector_wrap<T, A> make_vector_wrap(std::vector<T, A>& vec)
{ return vector_wrap<T, A>(vec); }

void something(vector_wrap<int> blah)
{
    for ( auto i : blah ) {
        std::cout << i << std::endl;
    }
    blah.push_back(blah.size());
    return;
}

void something_else(vector_wrap<int> blah)
{
    for ( auto& i : blah ) {
        i += i; // This must be disallowed
        std::cout << i << std::endl;
    }
    blah.push_back(blah.size()); // This will present a compiler error.
    return;
}

int main()
{
    std::vector<int> v{1,2,3,4,5,6};
    something(make_vector_wrap(v));
    something_else(make_vector_wrap(v));
}