#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <sstream>
using boost::property_tree::ptree;

namespace Entities {

    struct POST1 {
        std::string TokenNo;
        std::string CommandStatus;
        std::string CommandID;
        std::string CPUID;
        std::string ISEncrypted;

    };

    std::string to_json(POST1 const& o) {
        ptree out;
        out.put("POST1.TokenNo",          o.TokenNo);
        out.put("POST1.CommandStatus",    o.CommandStatus);
        out.put("POST1.CommandID",        o.CommandID);
        out.put("POST1.CPUID",            o.CPUID);
        out.put("POST1.ISEncrypted",      o.ISEncrypted);

        std::ostringstream oss;
        boost::property_tree::write_json(oss, out);
        return oss.str();
    }
}

// ADL trigger; `using Entities::to_json` would be roughly equivalent, but not
// make it clear that ADL is happening
void to_json();

int main() {
    Entities::POST1 obj { "1122", "0", "00", "A1234B1234", "0" };
    std::cout << to_json(obj);
}
