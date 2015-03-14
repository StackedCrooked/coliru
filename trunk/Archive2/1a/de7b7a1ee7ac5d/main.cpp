#include <iostream>
#include <boost/assign.hpp>
#include <boost/assign/list_of.hpp>
#include <tuple>
using namespace std;
using namespace boost::assign;

int main() {

    class NodeInfo {
      public:
        NodeInfo(int Parent, int childLeft, int childRight)
                : m_parent(Parent), m_childLeft(childLeft), m_childRight(childRight) {}

      private:
        int m_parent;
        int m_childLeft;
        int m_childRight;
    };

    typedef std::vector<NodeInfo> NodeInfos;
    NodeInfo node1(1,2,3), node2(3,4,5);
    NodeInfos infos = list_of(node1)(node2);

    typedef std::tuple<int, std::vector<NodeInfo> > Tuple;
    Tuple mytuple = std::make_tuple(10, infos);

    // I would have really liked the following:
    Tuple mytuple2 = std::make_tuple(10, 
            list_of(NodeInfo(1, 2, 3))(NodeInfo(3, 4, 5)).to_container(std::get<1>(mytuple2))
        );

    std::vector<Tuple> 
        mytuples = list_of<Tuple>(std::make_tuple(10, infos)),
        mytuples2;

    //// still figuring this out:
    // insert(mytuples2)(Tuple(10, infos))(Tuple(20, infos));
}
