#include <random>

int random_int_function(int i) 
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,100);

    int random_int = distribution(generator);  

    return i + random_int;
}

int main() {
    int a[random_int_function(10)] = {0};
}