#include <vector>
#include <iostream>
#include <algorithm>

class example
{
private:
    int m_sum;
public:
    example(std::initializer_list<int> parameters)
    {
        m_sum = std::accumulate(std::begin(parameters), std::end(parameters), 0);
    }

    int get_sum() const
    {
        return m_sum;
    }
};

int main() {

    example e = { 1, 2, 3, 4};
    std::cout << e.get_sum();
    return 0;
}