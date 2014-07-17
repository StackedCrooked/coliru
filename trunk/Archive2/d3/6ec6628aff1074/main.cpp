#include <cstddef>
std::size_t three() {
    return 3;
}

int main() 
{
    int i[three()];
    return 0;
}