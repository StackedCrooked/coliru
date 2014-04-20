#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>

struct Xfrm { 
    typedef double result_type;

    template <typename Gen>
    double operator()(double sd, Gen& randNormal, double data) const {
        return data + sd*randNormal();
    }
};

int main()
{
    boost::mt19937 gen(42); // seed it once
    boost::normal_distribution<double> nd(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > randNormal(gen, nd);

    std::vector<double> data(20, 0.0), nsyData;
    nsyData.reserve(data.size());

    double sd = 415*randNormal();

    std::transform(data.begin(), data.end(), std::back_inserter(nsyData), 
            boost::bind(Xfrm(), sd, boost::ref(randNormal), ::_1));
}
