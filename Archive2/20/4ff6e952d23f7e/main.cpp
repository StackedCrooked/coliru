#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace boost::uuids;

int main()
{
    random_generator gen;
    
    std::string as_text;

    for (int i = 0; i < 1; ++i)
    {
        uuid new_one = gen(); // here's how you generate one

        std::cout << "You can just print it: " << new_one << "; ";

        // or assign it to a string
        as_text = boost::lexical_cast<std::string>(new_one);

        std::cout << "as_text: '" << as_text << "'\n";

        // now, read it back in:
        uuid roundtrip = boost::lexical_cast<uuid>(as_text);

        assert(roundtrip == new_one);
    }
    
    try {
        std::cout << "Convert to UUID\n";
        boost::lexical_cast<uuid, std::string>(as_text + "34");
    }
    catch (boost::bad_lexical_cast&) {
        std::cout << "BAD UUID" << std::endl;   
    }
    
}
