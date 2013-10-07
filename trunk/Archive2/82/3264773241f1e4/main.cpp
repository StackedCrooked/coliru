#include <cassert>

int main () {
    const char* poolconst1 = "arf";
    const char* poolconst2 = "arf";
    char* pool1 = "meow";
    char* pool2 = "meow";
    assert( "[const char*] Strings are NOT pooled to the same address!" && poolconst1 == poolconst2 );
    assert( "[char* from const char*] Strings are NOT pooled to the same address!" && pool1 == pool2 );
}