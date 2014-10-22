#include <cstddef>

extern "C" const char* strings[];
const char* strings[] = {"Here", "are", "some", "strings"};

extern "C" const std::size_t strings_length;
const std::size_t strings_length = sizeof(strings)/sizeof(*strings);
