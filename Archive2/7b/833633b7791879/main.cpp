#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
#include <iostream>

bool is_valid_uuid(std::string const& maybe_uuid, boost::uuids::uuid& result) {
    using namespace boost::uuids;

    try {
        result = string_generator()(maybe_uuid); 
        return result.version() != uuid::version_unknown;
    } catch(...) {
        return false;
    }
}

int main() {
    std::string maybe_uuid;
    std::cout << "Enter a UUID: ";

    while (std::cin >> maybe_uuid)
    {
        boost::uuids::uuid result;
        bool is_valid = is_valid_uuid(maybe_uuid, result);
        std::cout << "\n'" << maybe_uuid << "' valid: " << std::boolalpha << is_valid << "\n";

        if (is_valid)
            std::cout << "Parsed value: " << result << "\n";
    }
}
