#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <array>
#include <iterator>
#include <cassert>
#include <random>

std::random_device device;
std::mt19937 engine(device());
std::uniform_int_distribution<> dist(1, 100);

template<typename T>
class matrix
{
public:
    matrix(std::size_t n) : _buf(n * n), _size(n)
    {
    }
    
    std::size_t & operator()(std::size_t x, std::size_t y)
    {
        return _buf[x * _size + y];
    }
    
    const std::size_t & operator()(std::size_t x, std::size_t y) const
    {
        return _buf[x * _size + y];
    }
    
    std::size_t size() const
    {
        return _size;
    }

private:
    std::vector<std::size_t> _buf;
    std::size_t _size;
};

std::size_t cost(const matrix<std::size_t> & mat, const std::vector<std::size_t> & path)
{
    auto cost = mat(path.back(), path.front());
    for (auto i = 0ull; i < path.size() - 1; ++i)
    {
        cost += mat(path[i], path[i + 1]);
    }
    return cost;
}

std::vector<std::size_t> tsp_approx(const matrix<std::size_t> & mat)
{
    std::vector<std::size_t> distances(mat.size());
    std::fill(distances.begin(), distances.end(), -1);
    std::vector<std::size_t> ret;
    
    auto update = [&]()
    {
        auto last = ret.back();
        for (auto i = 0ull; i < mat.size(); ++i)
        {
            if (i == last)
            {
                continue;
            }
            
            distances[i] = std::min(distances[i], mat(last, i));
        }
    };

    auto add = [&](std::size_t i)
    {
        ret.push_back(i);
        distances[i] = 0;
        update();
    };
    
    add(0);
    
    while (ret.size() != mat.size())
    {
        std::size_t dist = -1;
        std::size_t idx = -1;
        for (auto i = 0ull; i < mat.size(); ++i)
        {
            if (distances[i] == 0)
            {
                continue;
            }
            
            if (distances[i] < dist)
            {
                dist = distances[i];
                idx = i;
            }
        }
        
        add(idx);
    }
    
    return ret;
}

std::vector<std::size_t> tsp_bf(const matrix<std::size_t> & mat)
{
    std::vector<std::size_t> ret;
    ret.resize(mat.size());
    std::iota(ret.begin(), ret.end(), 0);
    auto min = ret;
    auto min_cost = cost(mat, ret);
    while (std::next_permutation(ret.begin(), ret.end()))
    {
        auto c = cost(mat, ret);
        if (c < min_cost)
        {
            min_cost = c;
            min = ret;
        }
    }
    return min;
}

int main()
{
    matrix<std::size_t> mat(5);
    
    for (auto i = 0ull; i < 5; ++i)
    {
        for (auto j = 0ull; j < 5; ++j)
        {
            if (i == j)
            {
                mat(i, j) = 0;
            }
            mat(i, j) = dist(engine);
        }
    }
    
    auto path = tsp_approx(mat);
    std::cout << cost(mat, path) << std::endl;
    std::copy(path.begin(), path.end(), std::ostream_iterator<std::size_t>(std::cout, ", "));
    std::cout << std::endl;
    path = tsp_bf(mat);
    std::cout << cost(mat, path) << std::endl;
    std::copy(path.begin(), path.end(), std::ostream_iterator<std::size_t>(std::cout, ", "));
    std::cout << std::endl;
}
