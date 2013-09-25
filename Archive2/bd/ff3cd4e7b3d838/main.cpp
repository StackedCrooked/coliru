#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
 
// This ctype facet classifies commas and endlines as whitespace
struct csv_whitespace : std::ctype<char> {
    static const mask* make_table()
    {
        // make a copy of the "C" locale table
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |=  space;  // comma will be classified as whitespace
        v[' '] &= ~space;      // space will not be classified as whitespace
        return &v[0];
    }
    csv_whitespace(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};
 
int main()
{
    std::string in = "Column 1,Column 2,Column 3\n123,456,789";
    std::string token;
 
    std::cout << "default locale:\n";
    std::istringstream s1(in);
    while(s1 >> token)
            std::cout << "  " << token << '\n';
 
    std::cout << "locale with modified ctype:\n";
    std::istringstream s2(in);
    s2.imbue(std::locale(s2.getloc(), new csv_whitespace));
    while(s2 >> token)
            std::cout << "  " << token<< '\n';
}