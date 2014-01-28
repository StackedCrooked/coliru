#include "derived.h"
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
int main()
{
    Base * b = new Derived();
    std::ofstream ofs("test.txt");
    boost::archive::text_oarchive oa(ofs);
    oa << b;
    ofs.close();
}
