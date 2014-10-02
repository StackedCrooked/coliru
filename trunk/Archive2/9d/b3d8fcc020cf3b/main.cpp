#include <iostream>
#include <string>
#include <functional>

struct sequence_iterator
{
public:
    sequence_iterator(int n) : _n{n} { }
    int operator * () { return _n; }    
    sequence_iterator& operator ++ () { ++_n; return *this; }
    bool operator != (sequence_iterator const& rhs) const { return _n != rhs._n; }
private:
    int _n;
};
    
struct sequence
{
public:
    sequence(int min, int max) : _min{min}, _max{max} { }    
    sequence_iterator begin() const { return { _min }; }
    sequence_iterator end() const { return { _max }; }
private:
    int _min;
    int _max;
};

int main()
{    
    for (auto i : sequence{0, 10})
    {
        std::cout << i;
    }
}