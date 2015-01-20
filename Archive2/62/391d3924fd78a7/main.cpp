 #include <random>
 #include <vector>
 #include <functional>
 #include <algorithm>
 
 struct foo
 {
    std::mt19937 mt;
    std::normal_distribution<> ndist;
    std::function<decltype(mt)::result_type()> rng_normal;
    
    foo()
    : mt{make_mersenne_twister()}
    , rng_normal{std::bind(ndist, std::ref(mt))}
    {}
    
    static std::mt19937 make_mersenne_twister()
    {
        std::minstd_rand seed_rng(std::random_device{}()); // random seed
        std::vector<int> seeds(16);
        
        std::generate(seeds.begin(), seeds.end(), seed_rng);
        
        std::seed_seq seq(seeds.begin(), seeds.end());
        return std::mt19937{seq};
    }
 };
 
int main() 
{}
