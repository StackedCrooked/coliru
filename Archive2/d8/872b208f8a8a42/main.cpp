#include <string>

static const char foo[] = "foo";


struct test {
    static const int x = 42;
    static const char bar[];
};

const char test::bar[] = "bar"; 

int main(){
}
