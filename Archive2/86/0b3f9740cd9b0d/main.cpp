#include <iostream>
#include <random>
 
int main()
{
    std::mt19937 gen;
 
    // Seed the engine with an unsigned int
    gen.seed(1);
    std::cout << "after seed by 1: " << gen() << '\n';
    std::cout << "after seed by 1: " << gen() << '\n';
    std::cout << "after seed by 1: " << gen() << '\n';
    gen.seed(1);
    std::cout << "after seed by 1: " << gen() << '\n';
    std::cout << "after seed by 1: " << gen() << '\n';
    std::cout << "after seed by 1: " << gen() << '\n';
 
    // Seed the engine with two unsigned ints
    std::seed_seq sseq{1, 2};
    gen.seed(sseq);
    std::cout << "after seed by {1,2}: " << gen() << '\n';
}