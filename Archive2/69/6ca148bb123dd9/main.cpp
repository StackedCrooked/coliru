#include <boost/random.hpp>
#include <boost/random/seed_seq.hpp>

int main()
{
    unsigned long seedv[4];
    seedv[0]=1;
    seedv[1]=2;
    seedv[2]=3;
    seedv[3]=4;

    boost::random::seed_seq ss({1ul, 2ul, 3ul, 4ul});

    boost::mt19937 gen2(ss);
}
