#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem.hpp>

using boost::filesystem::path;

    void prepend(path fname, std::vector<uint8_t> const& prepend_data)
    {
        using namespace boost::iostreams;
        auto size    = file_size(fname);
        auto resized = size + prepend_data.size();

        resize_file(fname, resized);
        mapped_file mf(fname.native().c_str());

        std::rotate(mf.data(), mf.data() + size, mf.data() + resized);
        std::copy(prepend_data.begin(), prepend_data.end(), mf.data());
    }

int main() {
    prepend("data.dat", { 1,2,3,4,5,6 });
}
