#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/range/istream_range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/irange.hpp>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;
using namespace boost;
using namespace boost::iostreams;

int main()
{
    string filename("test.mmap");
    { // Prepare file
        ofstream f(filename);
        copy(irange(0,24), ostreambuf_iterator<char>(f));
    }
    { // Work with memory mapped file
        mapped_file mm(filename);
        fill(mm, 0); // Works as range
        char *data=mm.data(); // Or as raw memory pointer
        copy("TEST!!!", data); // Copy to raw memory
    }
    { // print file contents
        ifstream f(filename);
        copy(istream_range<char>(f), ostream_iterator<char>(cout));
    }
}