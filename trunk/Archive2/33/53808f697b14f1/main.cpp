#include <boost/variant.hpp>
#include <boost/container/static_vector.hpp>
#include <iostream>
#include <vector>






template<typename T, int N = 10>
struct Vector
{
    bool empty()
    {
        using boost::get;
        if (auto smallvec = get<boost::container::static_vector<T, N>>(&storage))
        {
            return smallvec->empty();
        }
        else
        {
            return get<std::vector<T>>(storage).empty();
        }
    }

    std::size_t size() const
    {
        using boost::get;
        if (auto smallvec = boost::get<boost::container::static_vector<T, N>>(&storage))
        {
            return smallvec->size();
        }
        else
        {
            return boost::get<std::vector<T>>(storage).size();
        }
    }

    T& operator[](std::size_t index)
    {
        if (auto smallvec = boost::get<boost::container::static_vector<T, N>>(&storage))
        {
            return (*smallvec)[index];
        }
        else
        {
            return boost::get<std::vector<T>>(storage)[index];
        }
    }

    void push_back(const T& t)
    {
        if (auto smallvec = boost::get<boost::container::static_vector<T, N>>(&storage))
        {
            smallvec->push_back(t);
            if (smallvec->size() == smallvec->capacity())
            {
                storage = std::vector<T>(smallvec->begin(), smallvec->end());
            }
        }
        else
        {
            boost::get<std::vector<T>>(storage).push_back(t);
        }
    }

    boost::variant<boost::container::static_vector<T, N>, std::vector<T>> storage;
};



int main()
{
    Vector<int, 12> vec;
    for (int i = 1; i <= 20; ++i)
    {
        vec.push_back(i);

        for (auto i = 0 * vec.size(); i != vec.size(); ++i)
        {
            std::cout << vec[i] << ' ';
        }
        std::cout << std::endl;
    }
}
