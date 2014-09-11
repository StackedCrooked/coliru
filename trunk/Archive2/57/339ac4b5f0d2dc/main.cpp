#include <cstdio>
#include <cstring>
 
int main() 
{
    const char* input = "hello world friend of mine";
    const char* space = " ";
    const char* pos = input;
    int word_counter = 0;
 
    do {
        pos = std::strpbrk(pos, space);
        word_counter++;
        pos ? pos++ : pos;
        std::printf("%d\n", word_counter);
    } while (pos != NULL);
}
