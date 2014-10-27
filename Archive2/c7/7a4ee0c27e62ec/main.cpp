#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cassert>
#include <array>

std::vector<size_t> another = { 0, 3, 4, 1, 2 };
std::vector<size_t> another_partial = { 0, 3, 4, 1 };

template<typename T>
class matrix
{
public:
    matrix(std::size_t size) : _vec(size * size), _size{ size }
	{
	}
	
	T & operator()(std::size_t x, std::size_t y)
	{
        assert(x < _size && y < _size);
		return _vec[x * _size + y];
	}
    
    const T & operator()(std::size_t x, std::size_t y) const
	{
        assert(x < _size && y < _size);
		return _vec[x * _size + y];
	}

    std::size_t size() const
	{
		return _size;
	}
	
private:
	std::vector<T> _vec;
	std::size_t _size;
};

struct partial_solution
{
	std::vector<std::size_t> path;
	std::size_t cost = 0;
};

bool operator>(const partial_solution & lhs, const partial_solution & rhs)
{
    return lhs.cost > rhs.cost;
}

std::size_t bound(const matrix<std::size_t> & mat, const partial_solution & solution, std::size_t next)
{
	size_t b = 0;
    
    if (!solution.path.empty())
    {
        for (std::size_t i = 0; i < solution.path.size() - 1; ++i)
        {
            b += mat(solution.path[i], solution.path[i + 1]);
        }
        b += mat(solution.path.back(), next);
    }
    
    if (solution.path.size() == mat.size() - 1)
    {
        b += mat(solution.path.back(), next);
        b += mat(next, solution.path.front());
        
        if (solution.path == another_partial)
        {
            std::cout << "last: " << next << ", bound: " << b << "\n";
        }
        
        std::cout << "bound(v) = " << b << "\n";
    
        return b;
    }
    
    for (std::size_t i = 0; i < mat.size(); ++i)
    {
        if (std::find(solution.path.begin(), solution.path.end(), i) != solution.path.end())
        {
            continue;
        }

        std::size_t min_edge = std::numeric_limits<std::size_t>::max();

        for (std::size_t j = 0; j < mat.size(); ++j)
        {
            if (std::find(solution.path.begin(), solution.path.end(), j) != solution.path.end() || j == next || i == j)
            {
                continue;
            }
            
            if (mat(i, j) < min_edge)
            {
                min_edge = mat(i, j);
            }
        }

        if (std::max(min_edge, b) != std::numeric_limits<std::size_t>::max())
        {
            b += min_edge;
        }

        else if (b < min_edge)
        {
            b = min_edge;
        }
    }
    
    std::cout << "bound(v) = " << b << "\n";
    
    return b;
}

std::vector<std::size_t> tsp(const matrix<std::size_t> & mat)
{
    std::priority_queue<partial_solution, std::vector<partial_solution>, std::greater<>> solutions;

    {
        partial_solution best;
        best.cost = bound(mat, best, 0);
        best.path = { 0 };
    
        solutions.push(std::move(best));
    }
    
    while (solutions.top().path.size() != mat.size())
    {
        auto best = std::move(solutions.top());
        solutions.pop();
        std::cout << "best was: " << best.cost << "\n";
                
        for (std::size_t i = 0; i < mat.size(); ++i)
        {
            if (std::find(best.path.begin(), best.path.end(), i) != best.path.end())
            {
                continue;
            }
            
            partial_solution next;
            next.cost = bound(mat, best, i);
            next.path = best.path;
            next.path.push_back(i);
            
            solutions.push(std::move(next));
        }
    }
    
    assert(solutions.size());
    return std::move(solutions.top().path);
}

int main()
{
	matrix<std::size_t> mat(5);
    std::array<std::array<std::size_t, 5>, 5> arr = {{
        {{ 0, 14, 4, 10, 20 }},
        {{ 14, 0, 7, 8, 7 }},
        {{ 4, 5, 0, 7, 16 }},
        {{ 11, 7, 9, 0, 2 }},
        {{ 18, 7, 17, 4, 0 }}
    }};
    
    for (std::size_t i = 0; i < 5; ++i)
    {
        for (std::size_t j = 0; j < 5; ++j)
        {
            mat(i, j) = arr[i][j];
        }
    }
    
    auto path = tsp(mat);
    for (auto && elem : path)
    {
        std::cout << elem + 1 << " ";
    }
    
    std::size_t cost = 0;
    for (std::size_t i = 0; i < mat.size() - 1; ++i)
    {
        cost += mat(path[i], path[i + 1]);
    }
    cost += mat(path.back(), path.front());
    
    std::cout << "\n" << cost;
    
    //-----------
    std::vector<size_t> another = { 0, 3, 4, 1, 2 };
    cost = 0;
    for (std::size_t i = 0; i < mat.size() - 1; ++i)
    {
        cost += mat(another[i], another[i + 1]);
    }
    cost += mat(another.back(), another.front());
    
    std::cout << "\n" << cost;
}
