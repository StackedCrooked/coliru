#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace boost::property_tree;

int main() {
    ptree XMLobjectL;
    XMLobjectL.put("configuration.message.first", 10);

    write_xml("test.xml", XMLobjectL, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 1u));
}
