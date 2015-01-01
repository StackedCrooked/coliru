#include <fstream>
#include <ostream>
#include <cassert>

int main()
{
    std::ofstream ofs("/tmp/wut");
    ofs.close();
    assert(!ofs);
}