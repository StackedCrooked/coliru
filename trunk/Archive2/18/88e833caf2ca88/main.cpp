#include <assert.h>
#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

struct vertex {
    double x, y, z;
};

BOOST_FUSION_ADAPT_STRUCT(
                          vertex,
                          (double, x)
                          (double, y)
                          (double, z)
                          )

int main(int argc, char *argv[]) {
    std::vector<vertex> b_vertices;
    boost::iostreams::mapped_file mmap(
            "input.txt",
            boost::iostreams::mapped_file::readonly);

    const char* f = mmap.const_data();
    const char* l = f + mmap.size();

    namespace qi = boost::spirit::qi;

    bool ok = qi::phrase_parse(
            f,l,
             (
                   ("v"  >> qi::double_ >> qi::double_ >> qi::double_) |
                   ("vn" >> qi::double_ >> qi::double_ >> qi::double_)
              ) 
              % qi::eol,
            ('#' >> *(qi::char_ - qi::eol) >> qi::eol | qi::blank), b_vertices);

    std::cout << "parsed " << b_vertices.size() << " records\n";
}
