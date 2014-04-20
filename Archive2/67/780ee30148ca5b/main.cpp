#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>

struct Xfrm { 
    boost::mt19937 gen; // seed it once
    boost::normal_distribution<double> nd;
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > randNormal;

    double sd;

    Xfrm() 
        : gen(42), nd(0,1), randNormal(gen, nd), sd(415*randNormal())
    {
    }

    double operator()(double data) {
        return data + sd*randNormal();
    }
};

int main()
{

    std::vector<double> data(100000, 0.0), nsyData;
    nsyData.reserve(data.size());

    std::transform(data.begin(), data.end(), std::back_inserter(nsyData), Xfrm());
}
