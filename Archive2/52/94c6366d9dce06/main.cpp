#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>

int main()
{
    boost::mt19937 gen(42); // seed it once
    boost::normal_distribution<double> nd(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > randNormal(gen, nd);

    for (int i=0; i<100; ++i)
    {
        gen.seed(i);
        std::cout << randNormal() << " ";
    }
}
