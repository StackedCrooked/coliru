#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <memory>

template <class T> class test
{
private:
    std::unique_ptr<T[]> arr;
public:
    std::size_t rows;
    std::size_t cols;
    test(std::initializer_list<std::initializer_list<T>> r) : rows(r.size())
    {
        using init = const std::initializer_list<T>;
        cols = std::max_element(r.begin(), r.end(), [](init& lhs, init& rhs)
                                                    {return lhs.size() < rhs.size();}
                               )->size();
        arr = std::unique_ptr<T[]>(new T[rows*cols]);
        auto source = r.begin();
        auto dest = &arr[0];
        do  {
            std::copy(source->begin(), source->end(), dest);
            dest += cols;
        } while(++source != r.end())
    }
    T* operator[](std::size_t index)
    {
        return &arr[0] + index*cols;
    }
};

int main()
{
    test<int> a = {{1, 2, 3}, {4, 5, 6}};
    for(std::size_t i = 0; i < a.rows; ++i) {
        for(std::size_t j = 0; j < a.cols; ++j)
            std::cout << a[i][j] << ' ';
        std::cout << '\n';
    }
}
