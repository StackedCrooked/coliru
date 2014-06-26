#include <map>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
    vector<int>    A = {3  ,2 ,1 ,4  ,6 ,3 ,8 ,4};
    vector<double> B = {1.5,2 ,2 ,1.5,3 ,3 ,3 ,2};

    assert(A.size() == B.size());

    struct accum { 
        uintmax_t sum = 0; 
        size_t number_of_samples = 0; 
        void sample(int val) { sum += val; ++number_of_samples; }
    };
    map<double, accum> average_state;

    for(size_t i = 0; i<B.size(); ++i)
        average_state[B[i]].sample(A[i]);

    for(auto& entry : average_state)
    {
        auto& state = entry.second;
        auto effective_average = static_cast<double>(state.sum) / state.number_of_samples;
        std::cout << "Bucket " << entry.first << "\taverage of " << state.number_of_samples << " samples:\t" << effective_average << "\n";
    }
}
