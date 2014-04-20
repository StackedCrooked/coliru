#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>

int main()
{
    boost::mt19937 gen(42);
    boost::normal_distribution<double> nd(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > randNormal(gen, nd);

    std::vector<double> data(100000, 0.0), nsyData;
    nsyData.reserve(data.size());

    double sd = 415*randNormal();
    std::transform(data.begin(), data.end(), std::back_inserter(nsyData), 
            [sd,&randNormal](double data) { return data + sd*randNormal(); });

}
