#include <sstream>
#include <boost/property_tree/xml_parser.hpp>

int main()
{
  std::stringstream ss;
  ss << "<?xml ?><root><test /></root>";
  boost::property_tree::ptree pt;
  boost::property_tree::xml_parser::read_xml( ss, pt);

  for (auto r : pt.get_child(""))
    std::cout << r.first << std::endl;

  for (auto r : pt.get_child("root"))
    std::cout << r.first << std::endl;
    
  std::cout << std::endl << std::endl;

  std::stringstream ss2;
  ss2 << "<?xml version=\"1.0\"?><Response Location=\"910\" RequesterId=\"12\" SequenceNumber=\"0\"><Id>1</Id><Type>P</Type><StatusMessage></StatusMessage><Message>Error</Message></Response>";
  boost::property_tree::ptree pt2;
  boost::property_tree::xml_parser::read_xml(ss2, pt2);
  
  for (auto r : pt2.get_child("Response"))
    std::cout << r.first << std::endl;

return 0;
}