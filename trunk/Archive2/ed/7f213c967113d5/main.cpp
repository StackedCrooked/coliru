#include <boost/regex.hpp>
#include <boost/utility/string_ref.hpp>

template <typename StringT, typename C = typename StringT::value_type>
boost::basic_string_ref<C> GetFilename(StringT const& path) {

    // it's quite tricky to initialze the pattern generically:
    static auto re = [] {
        char const pattern[] = "[^\\\\/:]*$";
        std::basic_string<C> spattern(pattern, pattern + sizeof(pattern)-1);
        return boost::basic_regex<C>(spattern, boost::regex_constants::optimize);
    }();

    // the rest is plain sailing:
    boost::match_results<typename StringT::const_iterator> mr;
    if (boost::regex_search(path.begin(), path.end(), mr, re) && mr[0].matched)
        return { &*(mr[0].first), size_t(mr[0].length()) };
    return path;
}

#include <iostream>

int main() {

#if 0
    std::string fname = "/tmp/somedir/../other//./beautiful filenames.txt.0";
    std::cout << GetFilename(fname) << "\n";
#else
    std::wstring wname = L"D:\\Program Files (64)\\Something Else Entirely\\but works.just-the-same.exe";
    std::wcout << GetFilename(wname) << "\n";
#endif
}
