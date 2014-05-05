#include <iostream>
#include <vector>
#include <boost/crc.hpp>

int main()
{
    using namespace std;
    using namespace boost;

    crc_32_type  result;

    vector<char> buf1 {0, 7, 9, 13, 44, 55, 20, 1};
    result.process_bytes(buf1.data(), buf1.size());
    cout << "First attempt:\t" << result.checksum() << endl;
    
    vector<char> buf2 {7, 9, 45, 1, 2, 39};
    result.process_bytes(buf2.data(), buf2.size());
    cout << "Second attempt:\t" << result.checksum() << endl;

    crc_32_type check;
    check.process_bytes(buf2.data(), buf2.size());
    cout << "Second check:\t" << check.checksum() << endl;
}
