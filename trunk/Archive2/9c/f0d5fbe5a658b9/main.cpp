#include <string>
#include <boost/utility/string_ref.hpp>

template <typename StringT, typename C = typename StringT::value_type>
boost::basic_string_ref<C> GetFilename(StringT const& path) {
    static const C separators[4] = { '\\', '/', ':', 0 };
    return boost::basic_string_ref<C>(path).substr(path.find_last_of(separators) + 1);
}

#include <iostream>

int main() {
    for (std::string fname : {
            "/tmp/somedir/../other//./beautiful filenames.txt.0",
            "simple.txt",
            "",
        })
    {
        std::cout << "'" << fname << "' -> '" << GetFilename(fname) << "'\n";
    }

    for (std::wstring fname : {
            L"D:\\Program Files (64)\\Something Else Entirely\\but works.just-the-same.exe",
            L"\\UNCNAME\\Something Else Entirely\\network.dat",
            L"D://testing/test123",
            L"http://user:password@hostname:port/test123/resource?query=parameter#yo",
            L"E:beautiful filenames.txt.0",
            L"simple.txt",
            L"",
        })
    {
        std::wcout << "'" << fname << "' -> '" << GetFilename(fname) << "'\n";
    }
}
