#include <fstream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;
int main()
{
    ifstream input("some/file/", ifstream::binary);
    ofstream output;
    vector<char> buffer (istream_iterator<char>(input), istream_iterator<char>( ));
    for (int i=0; i<100; ++i)
    {
        string file_name = "/some/name";
        output.open (file_name.c_str(), ofstream::binary);
        copy( buffer.begin(), buffer.end(), std::ostream_iterator<char>(output));
        output.close();
    }
}