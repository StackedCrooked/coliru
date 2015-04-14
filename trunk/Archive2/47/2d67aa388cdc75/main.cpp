#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

int main() {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    auto uuidString = boost::lexical_cast<std::string>(uuid);
}
