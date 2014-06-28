#include <cstdio>
#include <chrono>
#include <vector>

struct succ
{
    int id;
    int cost;
    
    succ(int id, int cost) : id(id), cost(cost) { }
};

void get_succs(int src_state, std::vector<int>& ids, std::vector<int>& costs)
{
    static int id = 0;
    static int cost = 0;
    ids.clear();
    costs.clear();
    ids.push_back(id++);
    costs.push_back(cost++);
}

std::vector<succ> get_succs(int src_state)
{
    static int id = 0;
    static int cost = 0;
    
    std::vector<succ> succs;
    succs.emplace_back(id++, cost++);
    
    return succs;
}

int main(int argc, char *argv[])
{
    const int num_iterations = 1000;
    
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; ++i) {
            std::vector<int> ids;
            std::vector<int> costs;
            get_succs(0, ids, costs);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        printf("%0.6f seconds\n", std::chrono::duration<double, std::ratio<1>>(end - start).count());
    }
    
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; ++i) {
            std::vector<succ> succs = get_succs(0);
        }
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        printf("%0.6f seconds\n", std::chrono::duration<double, std::ratio<1>>(end - start).count());
    }
    return 0;
}