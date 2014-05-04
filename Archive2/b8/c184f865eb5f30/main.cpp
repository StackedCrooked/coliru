#include <iostream>

#define PARAMS "Hillow", " whirled"
#define TEST(p1, p2) p1 p2
#define TEST_MACRO(m) TEST(m)

void test() 
{   
   const char* c = TEST_MACRO(PARAMS);
   std::cout << c;
}

int main() {
    test();
}