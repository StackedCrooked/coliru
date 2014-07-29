#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace MessageBox {
  void
  Show(std::string const& msg, std::string const&) {
    std::cerr << msg << '\n';
  }
}

struct HDRFIleDescriptor {
  std::string filename;
  std::string interleave;
};

 bool PreloadBsq(HDRFIleDescriptor &hdr_descr, std::vector<char> & content)
    {
        std::string data_file = hdr_descr.filename.substr(0, hdr_descr.filename.length() - 3);
        data_file += hdr_descr.interleave;

        std::ifstream bsq_file;

        bsq_file.open(data_file, std::ios::binary | std::ios::in);

        if (!bsq_file) {
            MessageBox::Show("Can't open the file!", "Error!");
            return false;               
        }

        bsq_file.seekg(0, std::ios_base::end);        
        std::streamsize size = bsq_file.tellg();

        content.resize(size);

        bsq_file.seekg(0, std::ios_base::beg);

        bsq_file.read(&content[0], size);

        return true;
    }
   
int
main() {
  HDRFIleDescriptor desc{"data.dat", "dat"};
  std::vector<char> data;
  PreloadBsq(desc, data);
  if (std::find_if(data.begin(), data.end(),
                   [] (char c) { return c != 0; }) != data.end())
    std::cout << "Success!\n";
  else
    std::cout << "Failure.\n";
}

// [ ] [nightshade] /tmp > g++ -Wall -Wextra -std=c++11 -pedantic foo.cpp -o foo
// [ ] [nightshade] /tmp > dd if=/dev/urandom of=data.dat bs=1M count=1024
// 1024+0 records in
// 1024+0 records out
// 1073741824 bytes (1.1 GB) copied, 60.9238 s, 17.6 MB/s
// [ ] [nightshade] /tmp > ./foo
// Success!
// [i] [nightshade] /tmp > 