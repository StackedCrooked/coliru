#include <string>
#include <vector>


// This Range is basically a pair of pointers
// with some added convenience.
template<typename T>
struct Range
{
    Range() : begin_(), end_() {}
    
    Range(T* b, T* e) : begin_(b), end_(e) {}
    
    T* begin() { return begin_; }
    T* end() { return end_; }
    
    const T* begin() const { return begin_; }
    const T* end() const { return end_; }
    
    int size() const { return end_ - begin_; }
    
    T& front() { return *begin_; }
    T& back() { return *(end_ - 1); }

private:
    T* begin_;
    T* end_;
};


int main()
{
    int n[] = { 1, 2, 3 };
    
    Range<int> range(std::begin(n), std::end(n));
    
    Range<const int> const_copy = range; // error!
}
