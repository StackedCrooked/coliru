#include <cstring>
#include <string>

struct TestStruct
{
    int a;
    std::string b;
};


int main() {
    TestStruct t;
    std::memset(&t, 0, sizeof(TestStruct));
}