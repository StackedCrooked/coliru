#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>
#include <stdexcept>
#include <string>

template <class T>
class DP
{
public:
    using value_type                    = T;
    using key_type                      = std::size_t;
    using check_function_type           = std::function<bool(key_type)>;
    using work_function_type            = std::function<key_type(key_type)>;
    using check_work_funcions_pair_type = std::pair<check_function_type, work_function_type>;

public:
    DP(key_type b, key_type e, std::vector<check_work_funcions_pair_type>&& f)
        :   _begin(b),
            _dp(e - b, 0),
            _functions(std::move(f))
    {
        *_dp.begin() = 1;
    }

    void calculate()
    {
        for(std::size_t i = 0; i < _dp.size(); ++i)
            for(const auto& p: _functions)
                if(p.first(i + _begin))
                    _dp.at(i) += _dp.at(p.second(i + _begin) - _begin);
    }

    value_type operator[] (key_type k) const
    {
        if(k > (_begin + _dp.size()))
            throw std::out_of_range
            (
                "DP: operator[]: " +
                    std::to_string(k) +
                        " is greater than " +
                    std::to_string(_begin + _dp.size())
            );
        if(k < _begin)
            throw std::out_of_range
            (
                "DP: operator[]: " +
                    std::to_string(k) +
                        " is less than " +
                    std::to_string(_begin) +
                        "(begin)"
            );
        return _dp.at(k - _begin);
    }

private:
    key_type _begin;
    std::vector<T> _dp;
    std::vector<check_work_funcions_pair_type> _functions;
};

int main()
{
    DP<int> dp
    (
        2, 37,
        {
            {
                [] (std::size_t v)
                {
                    return v >= 4;
                },
                [] (std::size_t v)
                {
                    return v - 2;
                }
            },
            {
                [] (std::size_t v)
                {
                    return v % 4 == 0 && v >= 8;
                },
                [] (std::size_t v)
                {
                    return v / 4;
                }
            }
        }
    );

    dp.calculate();
    std::cout << dp[36] << std::endl;
    return 0;
}
    