#include <cstddef>

class some_container
{
public:
    explicit some_container(std::size_t size) : size(size) {}
private:    
    std::size_t size;
};

int main()
{
    some_container sc(-1);
}
