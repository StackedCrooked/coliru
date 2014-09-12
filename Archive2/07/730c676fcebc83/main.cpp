#include <boost/property_tree/ptree.hpp>
#inlcude <sstream>

int main()
{
    using boost::property_tree::ptree;
	ptree   pt;

	std::string m_Guid, m_CustomerId, m_Name, m_Version;

	pt.add("License.Unalterable.Signed.Guid", m_Guid);
	pt.add("License.Unalterable.Signed.CustomerId", m_CustomerId);
	pt.add("License.Unalterable.Signed.Name", m_Name);
	pt.add("License.Unalterable.Signed.Version", m_version);

	std::ostringstream oss;
	write_xml(oss, pt); // error happened on this function
}