#include <cassert>
#include <cmath>

struct precondition_call { };
struct in_call { };

template<typename F>
void operator+(precondition_call const&, F&& f) {
    f();
}

template<typename F>
void operator+(in_call const&, F&& f) {
    
}

#define REQUIRE { precondition_call() + [&]
#define IN() (); in_call() +
#define ENSURE () + postcondition_call()

double sqrt(double x)
REQUIRE {
    assert(x >= 0.0);
} IN {
    
} ENSURE (auto result) {
    
}

int main() {
    
}