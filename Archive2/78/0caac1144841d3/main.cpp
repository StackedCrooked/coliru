#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>
#include <boost/phoenix.hpp>

namespace phx = boost::phoenix;
using namespace phx::arg_names;

int main()
{
    boost::mt19937 gen(42); // seed it once
    boost::normal_distribution<double> nd(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > randNormal(gen, nd);

    std::vector<double> data(20, 0.0), nsyData;
    nsyData.reserve(data.size());

    double sd = 415*randNormal();

    std::transform(data.begin(), data.end(), std::back_inserter(nsyData), phx::bind(randNormal) * sd + arg1 );

    for (size_t i=0; i<nsyData.size(); ++i)
        std::cout << nsyData[i] << " ";
}
