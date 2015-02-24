#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>
#include <iostream>

using boost::uuids::uuid;
using boost::conversion::try_lexical_convert;

int main() {
    std::string maybe_uuid("00000000-0000-0000-0000-000000000000");
    std::cout << "Enter a UUID: ";

    uuid result;
    bool is_valid = try_lexical_convert<uuid>(maybe_uuid, result);
    std::cout << "\n'" << maybe_uuid << "' valid: " << std::boolalpha << is_valid << "\n";
    if (is_valid)
        std::cout << "Parsed value: " << result << "\n";
    
}
