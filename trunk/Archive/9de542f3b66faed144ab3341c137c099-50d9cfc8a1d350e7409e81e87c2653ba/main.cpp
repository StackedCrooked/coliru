#include <iostream>
#include <string>
#include <utility>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vec)
{
    for (const auto & x : vec)
    {
        os << x << " ";
    }
    return os;
}


struct range
{
    range(int * b, int * e) : begin(b), end(e) {}
    
    std::size_t size() const { return end - begin; }
    
    std::pair<range, range> split()
    {
        auto s2 = size() / 2;
        return std::make_pair(range(begin, begin + s2),
                              range(begin + s2, end + s2));
    }
    
    int & operator[](int n)
    {
        return begin[n];
    }
    
    int * begin;
    int * end;    
};


std::ostream& operator<<(std::ostream& os, const range & r)
{
    for (auto i = r.begin; i != r.end; ++i)
    {
        os << (*i) << "  ";
    }
    return os;
}


void qsort(range & v)
{    
    std::cout <<  v << std::endl;
            
    auto size = v.end - v.begin;
    if (size <= 1)
        return;
        
    if (v.size() == 2 && v[1] < v[0])
    {
        std::cout <<  v << std::endl;
        std::swap(v[0], v[1]);
    }
        
        
    auto p = v.size() / 2;
    
    
    std::size_t i = 0, j = v.size() - 1;
    for (;;)
    {        
        while (v[i] < v[p] && i < p) i++;
        
        std::size_t j = v.size() - 1;
        while (v[j] > v[p] && j > p) j--;
        
        if (i < p)
        {
            if (j > p)
            {
                std::swap(v[i], v[j]);
                std::cout <<  v << std::endl;
            }
            else
            {
                v.insert(v.begin() + p + 1, v[i]);
                v.erase(v.begin() + 1);
                std::cout <<  v << std::endl;
            }
        }        
        else if (j > p)
        {
            auto copy = v[j];
            v.erase(v.begin() + j);
            v.insert(v.begin(), copy);
            std::cout <<  v << std::endl;         
        }
        else
        {
            
            qsort(left_side);
            qsort(right_side);
            
            break;
        }
    }
}


std::vector<int> v = { 6, 5, 1, 4, 2, 3 };


int main()
{
    range r(&v[0], &v[0] + v.size());
    
    qsort(r);
    std::cout << "Sorted: " << v << std::endl;
}


