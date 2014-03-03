#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::uuids;

int main()
{
    random_generator gen;

    for (int i = 0; i < 10; ++i)
    {
        uuid new_one = gen(); // here's how you generate one

        std::cout << "You can just print it: " << new_one << "; ";

        // or assign it to a string
        std::string as_text = boost::lexical_cast<std::string>(new_one);

        std::cout << "as_text: '" << as_text << "'\n";

        // now, read it back in:
        uuid roundtrip = boost::lexical_cast<uuid>(as_text);

        assert(roundtrip == new_one);
    }
}
