#include <utility>


struct rect : std::pair<int, int>
{
    rect() : width(first), height(second) {}
    int& width;
    int& height;
};

int main()
{
    rect r;
    r.width = 3;
}