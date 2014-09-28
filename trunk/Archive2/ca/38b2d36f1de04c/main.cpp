#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace po = boost::program_options;

struct command {
    command(const std::string& name = {},
            const po::options_description& desc = {})
        : name(name), 
          desc(boost::make_shared<po::options_description>(desc))
    {
    }

    command& operator=(const command& other) = default;
  private:
    std::string name;
    boost::shared_ptr<po::options_description> desc;
};

int main() {
    command a, b;
    b = a;
}
