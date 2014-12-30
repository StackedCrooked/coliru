#include <array>

// header:
class SomeThing
{
   SomeThing() {}
   
   static std::array<SomeThing, 64> lookup_table_0;
   friend decltype(lookup_table_0);
   static SomeThing lookup_table_1[64];
};

std::array<SomeThing, 64> SomeThing::lookup_table_0; // error

int main() {}