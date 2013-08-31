#include <iostream>

int main()
{
    short x, result, result2;
    
    x = 246;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    x = -246;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    std::cout << std::endl;

    x = 327;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    x = -327;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    std::cout << std::endl;

    x = 3270;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    x = -3270;
    result = (-x > 0) ? -((-x) / 327) : x / 327;
    result2 = x / 327;
    std::cout << result << " vs. " << result2 << std::endl;

    std::cout << std::endl;
    
}