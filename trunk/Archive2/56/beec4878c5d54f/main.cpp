#include <boost/regex.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

namespace io = boost::iostreams;
using sref   = boost::string_ref;
using regex  = boost::regex;

typedef std::map<std::string::difference_type, sref> hitmap;
hitmap hits;

void regres(const boost::match_results<const char*>& what) {
    hits[what.position()] = sref(what[0].first, what[0].length());
}

int main() {
    io::mapped_file_params params("/etc/dictionaries-common/words");
    params.flags = io::mapped_file::mapmode::priv;
    io::mapped_file mapped(params);
    std::replace(mapped.data(), mapped.end(), '\n', '|');

    regex const wordlist(mapped.begin(), mapped.end());

    io::mapped_file_source book("/etc/dictionaries-common/words");

    boost::cregex_iterator lex(book.begin(), book.end(), wordlist), end;
    std::for_each(lex, end, &regres);
}
