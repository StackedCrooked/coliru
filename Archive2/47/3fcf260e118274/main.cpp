#include <boost/random.hpp>
#include <boost/random/seed_seq.hpp>

int main()
{
    boost::random::seed_seq ss({1ul, 2ul, 3ul, 4ul});

    boost::mt19937 gen2(ss);
}
