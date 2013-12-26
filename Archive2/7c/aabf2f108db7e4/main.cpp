#include <iostream>
#include <fstream>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;

int main(void)
{
    cout << boolalpha;

    ifstream ifs("a.out", ios::binary);
    boost::iostreams::file_sink ofile("a.out.boost.gz");

    boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
    out.set_auto_close(true);

    out.push(boost::iostreams::gzip_compressor());
    out.push(ofile);

    cout << "out.is_complete(): " << out.is_complete() << endl;
    cout << "ifs.is_open()? "     << ifs.is_open()     << endl;
    cout << "ofile.is_open()? "   << ofile.is_open()   << endl;

    boost::iostreams::copy(ifs, out);

    cout << "out.is_complete(): " << out.is_complete() << endl;
    cout << "ifs.is_open()? "     << ifs.is_open()     << endl;
    cout << "ofile.is_open()? "   << ofile.is_open()   << endl;
}
