#include <random>

template<class URNG>
void f(URNG&& g) {
    typedef typename URNG::result_type rng_result;
}

int main(int argc, char** argv) {
    std::mt19937_64 rng;
    f(rng);
    
    return 0;
}