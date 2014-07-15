#include <vector>
#include <iostream>
#include <cstdlib>

std::vector<std::pair<int, int> > solve(int c) {
    std::vector<int> a;
    for (int i = 1; i * i <= c; ++i)
        if (c % (i*i) == 0) a.push_back(i);

    std::vector<std::pair<int, int> > solutions;
    solutions.reserve(a.size());
    for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
        const int& a = *it;
        solutions.push_back(std::pair<int, int>(a, c / (a*a)));
    }

    return solutions;
}
    
int main(int /*argc*/, char* argv[]) {
    int c = atoi(argv[1]);
    
    std::vector<std::pair<int,int> > solutions = solve(c);
    
    std::cout << "Solutions to a^2 * b = " << c << "\n"
                 "(a, b)\n";
    
    for (std::vector<std::pair<int,int> >::iterator it = solutions.begin(); it != solutions.end(); ++it)
        std::cout << '(' << it->first << ", " << it->second << ")\n";
}