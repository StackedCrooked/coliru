#include <sstream>
#include <string>
#include <boost/property_tree/xml_parser.hpp>

int main()
{
  std::stringstream ss;
  ss << "<?xml ?><root><test /></root>";
  boost::property_tree::ptree pt;
  boost::property_tree::xml_parser::read_xml(ss, pt);

  // There is no data associated with root node...
  std::string s(pt.get<std::string>("root"));
  std::cout << "EXAMPLE1" << std::endl << "Data associated with root node: " << s << std::endl;

  // ...but there is a child node.
  std::cout << "Children of root node: ";
  for (auto r : pt.get_child("root"))
    std::cout << r.first << std::endl;
    
  std::cout << std::endl << std::endl;
  
  std::stringstream ss2;
  ss2 << "<?xml ?><root>dummy</root>";
  boost::property_tree::xml_parser::read_xml(ss2, pt);

  // This time we have a string associated with root node
  std::string s2(pt.get<std::string>("root"));
  std::cout << "EXAMPLE2" << std::endl << "Data associated with root node: " << s2 << std::endl;

return 0;
}