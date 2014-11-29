#include <iostream>
#include <string>
#include <vector>

void render_doodle(const auto& doodle)
{
    std::cout << "Hiya!" << std::endl;
}

int main()
{
    render_doodle(7);
    render_doodle("Test");
}
