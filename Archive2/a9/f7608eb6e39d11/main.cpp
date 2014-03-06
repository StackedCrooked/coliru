#include <iostream>
#include <string>

class S
{
public:
    S(const char *s) : s(s) {}
    
    operator const char*() const { return s; }
    
private:
    const char *const s;
};

const S array[] = "123";

int main(void)
{
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); ++i) {
        std::cout << i << ": " << array[i] << std::endl;
    }
    return 0;
}