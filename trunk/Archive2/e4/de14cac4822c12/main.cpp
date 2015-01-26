#include <boost/circular_buffer.hpp>

struct pkt { int data; };

int main() {
    // Boost Circular Queue -- This works fine
    typedef boost::circular_buffer<pkt> pkt_queue;
    
    pkt_queue a_queue(3);

    // Vector of queues - This has errors, i also wish to initialize the vector
    std::vector<pkt_queue> per_port_pkt_queue;

    per_port_pkt_queue.emplace_back(3);
    per_port_pkt_queue.emplace_back(3);
    per_port_pkt_queue.emplace_back(3);

    // or
    per_port_pkt_queue.assign(20, pkt_queue(3)); // twenty 3-element queues
}

