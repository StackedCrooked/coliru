using max_align_t = double;
#include <iostream>
#include <random>
#include <initializer_list>
#include <cstddef>
#include <cstdint>

template<typename ResultType = int>
class rd_seed_seq
{
private:
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> dist;
    
public:
    using result_type = ResultType;
    
    rd_seed_seq() {}
    
    template<typename InputIt>
    rd_seed_seq(InputIt ib, InputIt ie)
    {}
    
    rd_seed_seq(std::initializer_list<result_type>)
    {}
    
    template<typename RaIt>
    void generate(RaIt rb, RaIt re)
    {
        for(;rb != re; ++rb)
        {
            *rb = dist(rd);
        }
    }
    
    constexpr auto size() const noexcept -> std::size_t
    { return 0; }
    
    template<typename OutputIt>
    void param(OutputIt ob)
    {}
};

int main()
{
    rd_seed_seq<> seed_seq{};
    auto mt = std::mt19937_64{ seed_seq };
}