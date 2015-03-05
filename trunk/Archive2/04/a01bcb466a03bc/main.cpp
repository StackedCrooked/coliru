#include <boost/filesystem.hpp>
#include <iostream>
namespace fs = boost::filesystem;

template <typename StringT>
StringT GetFilename(StringT const& path) {
    return fs::path(path).filename().string<StringT>();
}

int main() {
#ifndef _WIN32
    std::string fname = "/tmp/somedir/../other//./beautiful filenames.txt.0";
    std::cout << GetFilename(fname) << "\n";
#else
    std::wstring wname = L"D:\\Program Files (64)\\Something Else Entirely\\but works.just-the-same.exe";
    std::wcout << GetFilename(wname) << "\n";
#endif
}
