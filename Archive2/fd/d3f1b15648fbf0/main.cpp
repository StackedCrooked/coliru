#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>

int main()
{
    using boost::property_tree::ptree;
	ptree   pt;

	std::string m_Guid, m_CustomerId, m_Name, m_version;

	pt.add("License.Unalterable.Signed.Guid", m_Guid);
	pt.add("License.Unalterable.Signed.CustomerId", m_CustomerId);
	pt.add("License.Unalterable.Signed.Name", m_Name);
	pt.add("License.Unalterable.Signed.Version", m_version);

	std::ostringstream oss;
	write_xml(oss, pt);
}