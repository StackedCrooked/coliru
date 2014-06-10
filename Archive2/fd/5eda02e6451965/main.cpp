#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/mpl/string.hpp>
#include <iostream>

using namespace std;
using namespace boost;

typedef fusion::map
<
    fusion::pair<mpl::string<'one'>, unsigned>,
    fusion::pair<mpl::string<'two'>, unsigned>,
    fusion::pair<mpl::string<'thre', 'e'>, unsigned>,
    fusion::pair<mpl::string<'four'>, unsigned>
> OccurrenceStorage;

struct Printer
{
    template<typename Pair>
    void operator()(Pair p) const
    {
        cout << mpl::c_str<typename Pair::first_type>::value << " : " << p.second << endl;
    }
};

int main()
{
    OccurrenceStorage occurrence_storage(0, 0, 1, 3);

    ++fusion::at_key< mpl::string<'one'> >(occurrence_storage);
    fusion::at_key< mpl::string<'two'> >(occurrence_storage) = 2;
    fusion::at_key< mpl::string<'thre', 'e'> >(occurrence_storage) +=2;
    ++fusion::at_key< mpl::string<'four'> >(occurrence_storage);

    fusion::for_each(occurrence_storage, Printer());
}

