#include <string>
#include <iostream>

#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/mpl.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

struct  myStructType
{
    double val1;
    double val2;
    char letter;
    int number;
}; 

BOOST_FUSION_ADAPT_STRUCT(
    myStructType,
    (double, val1)
    (double, val2)
    (char, letter)
    (int, number)
)   



template <typename Sequence>
struct XmlFieldNamePrinter
{
    template <typename Zip>
    void operator() (const Zip& v) const
    {

        typedef typename boost::remove_const<
                        typename boost::remove_reference<
                            typename fusion::result_of::at_c<Zip,0>::type
                        >::type 
                    >::type Index;

        std::string field_name = fusion::extension::struct_member_name<Sequence,Index::value>::call();

        std::cout
            << '<' << field_name << '>'
            << fusion::at_c<1>(v)
            << "</" << field_name << '>'
            ;
    }
};
template<typename Sequence>
void printXml(Sequence const& v)
{
    typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Sequence>::value > Indices; 
    fusion::for_each(fusion::zip(Indices(),v), XmlFieldNamePrinter<Sequence>());
}

int main()
{
    myStructType saveMe = { 3.4, 5.6, 'g', 9};
    printXml(saveMe);
}