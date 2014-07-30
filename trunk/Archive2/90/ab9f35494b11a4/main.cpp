#include <iostream>
#include <string>
#include <sstream>

void copy_names( std::istream& input, std::ostream& output )
{
    static const std::string name_tag = "name = " ;
    static const auto name_tag_sz = name_tag.size() ;
    static const std::string product_tag = ", product =" ;

    std::string line ;
    while( std::getline( input, line ) )
    {
        auto begin = line.find(name_tag) ; // try to find name_tag
        if( begin != std::string::npos ) // if found
        {
            begin += name_tag_sz ; // set begin of name to char just after name_tag

            const auto end = line.find( product_tag, begin  ) ; // try to find product_tag
            // if found, name is everything up to the product_tag,
            // else everything up to end of line
            auto len = end != std::string::npos ? end-begin : end ;

            output << line.substr( begin, len ) << '\n' ; // extract ant write the name
        }
    }
}

int main()
{
    std::istringstream file( R"(
                                    userid = xxsfdfafa, name = vinnidrk, product = 12341,
                                    otherfield = 1
                                    otherfield2 = 2
                                    otherfield3 = 4

                                    userid = asdsada, name = anotherperson, product = 424123,
                                    otherfield = 3
                                    otherfield2 = 5
                                    otherfield3 = 1

                                    userid = vhhvjv, name = a third person, product = 999,
                                    otherfield = 8
                                    otherfield2 = 3
                                    otherfield3 = 4
                               )" ) ;
    copy_names( file, std::cout ) ;
}
