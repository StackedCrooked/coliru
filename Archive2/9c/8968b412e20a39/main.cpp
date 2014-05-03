int checkBitrate(int nBitrate)
{
    static int const table[] = { 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0 };
    int const* lu = table;
    do if (nBitrate <= *lu) return *lu; while (*++lu);
    return 320;
}

#include <iostream>

int main() {
    for (int br = 0; br != 420; ++br)
        std::cout << checkBitrate(br) << " ";
}
