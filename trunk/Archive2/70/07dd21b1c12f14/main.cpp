#include <boost/property_tree/xml_parser.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

namespace pt = boost::property_tree;
namespace io = boost::iostreams;
namespace fs = boost::filesystem;

int main()
{
    fs::wpath const fname = L"test撧.xml";
    io::file_descriptor_source fs(fname);
    io::stream<io::file_descriptor_source> fsstream(fs);

    pt::ptree xml;
    pt::read_xml(fsstream, xml);

    for (auto const& node : xml.get_child("root"))
        std::cout << node.first << ": " << node.second.get_value<std::string>() << "\n";
}