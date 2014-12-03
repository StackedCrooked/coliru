/** Read the whole file as-is into a container (vector).

    $ make CXX='g++ -std=c++11' read-binary-file && ./read-binary-file read-binary-file.cpp
*/
#ifdef WINDOWS
#include <fcntl.h>
#include <io.h>
#endif
#include <algorithm> // copy
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  using namespace std;
#ifdef WINDOWS
  _setmode(_fileno(stdout), _O_BINARY); // turn off `\n` -> `\r\n` translation
#endif

  if (argc != 2) {
    cerr << "Usage: read-file <file>\n";
    return 2;
  }

  ifstream file(argv[argc-1], ios::in | ios::binary | ios::ate);
  if (!file) return 1; // error
  const ifstream::pos_type file_size = file.tellg();
  vector<char> data(file_size);  // use vector instead of string to
    			 // stress that it is a binary data
  file.seekg(0, ios::beg);
  if(!file.read(&data[0], file_size)) return 1; // error
  // do whatever you like with *data* here...
  copy(begin(data), end(data), ostreambuf_iterator<char>(cout));
}