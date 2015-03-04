#include <iostream>
#include <string>
#include <limits>

int main()
{
    std::uint64_t huge_val_unsigned = std::numeric_limits<std::uint64_t>::max();
    std::clog << "huge_val_unsigned " <<  huge_val_unsigned << "\n";
    std::int64_t huge_val_signed = static_cast<std::int64_t>(huge_val_unsigned);
    std::clog << "huge_val_signed " << huge_val_signed << "\n";
}
