#include <iostream>

int main()
{
    char def[] = "B\347\xff\xff~<\030";
    
    for (unsigned char c : def) {
        for (int i = 0; i < 8; ++i) {
            if (c & (1 << i)) {
                std::cerr << "\u2661";
            }
            else {
                std::cerr << " ";
            }
        }
        std::cerr << std::endl;
    }
}
