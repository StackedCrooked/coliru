#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/view.hpp>

using namespace boost;

int main()
{
    typedef fusion::vector<int, int, int> Tuple3;
    Tuple3 v1(1,2,3);
    Tuple3 v2(4,5,6);

    typedef fusion::vector<Tuple3&, Tuple3&> VVector;
    VVector vv(v1,v2);

    typedef fusion::zip_view<VVector> ZipView;
    auto zv = fusion::as_vector(ZipView(vv));
    typedef fusion::flatten_view<decltype(zv)> FlattenView;
    auto fv = FlattenView(zv);

    // proof of the pudding:
    auto first = fusion::begin(fv);
}
