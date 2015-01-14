#include <iostream>
#include <string>
#include <vector>

class Test
{
    public:
    Test(int dim) : m_data(dim) {}
    bool& operator[](int idx) { return m_data.data()[idx]; }
    std::vector<bool> m_data;
};

int main()
{
    Test test(10);
    test[4] = true;
    std::cout << test[4] << std::endl;
}
