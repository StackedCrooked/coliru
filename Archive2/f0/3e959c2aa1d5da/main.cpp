#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

int main()
{
    using namespace std;
    using namespace boost;
    using namespace boost::accumulators;

    ifstream inNew("A.csv");

    vector<accumulator_set<double, stats<tag::mean, tag::variance>>> acc;

    if (inNew)
    {
        string line;
        while (getline(inNew, line))
        {
            std::vector<double> values;
            auto f(line.begin()), l(line.end());
            if (qi::phrase_parse(f,l,qi::auto_ % ',',qi::space,values))
            {
                acc.resize(std::max(acc.size(), values.size()));
                auto accit=acc.begin();
                for (auto v : values)
                    (*accit++)(v);
            } else
            {
                std::cerr << "Skipping bad line '" << line << "'\n";
            }
        }
        
        for (size_t i = 0; i < acc.size(); ++i)
        {
            cout << "\n------- column " << (i + 1) << endl;
            cout << "Expected return is: " << mean(acc[i]) << endl;
            cout << "Variance: " << variance(acc[i]) << endl;
            cout << "Std Dev: " << sqrt(variance(acc[i])) << endl;
        }
    }

    inNew.close();
}
