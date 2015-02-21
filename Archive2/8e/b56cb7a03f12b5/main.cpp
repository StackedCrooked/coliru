#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace boost;

int main() {
    std::map<int64_t, int64_t> foo;
    filesystem::path myFile = filesystem::current_path() / "myfile.dat";

    if (filesystem::exists(myFile))
    {
        filesystem::ifstream ifs(myFile.native());
        archive::text_iarchive ta(ifs);

        ta >> foo; // foo is empty until now, it's fed by myFile

        std::cout << "Read " << foo.size() << " entries from " << myFile << "\n";
    } else {
        for (int i=0; i<100; ++i) foo.emplace(rand(), rand());
        filesystem::ofstream ofs(myFile.native());
        archive::text_oarchive ta(ofs);

        ta << foo; // foo is empty until now, it's fed by myFile
        std::cout << "Wrote " << foo.size() << " random entries to " << myFile << "\n";
    }

}
