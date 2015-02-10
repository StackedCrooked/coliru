#include <boost/intrusive/list.hpp>
#include <boost/shared_ptr.hpp>

struct Event {};

struct Node : boost::intrusive::list_base_hook<> {
    boost::shared_ptr<Event> event { new Event };
};

typedef boost::intrusive::list<Node> event_list;

int main() {
    std::vector<Node> nodes(10);

    event_list pending;
    pending.push_back(nodes[3]);
    pending.push_back(nodes[7]);
}
