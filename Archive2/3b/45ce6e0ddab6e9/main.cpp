#include <cstdint>

class foo{
   uint32_t flags_ext[16];
   uint32_t& flags = flags_ext[0];
};

int main() {}