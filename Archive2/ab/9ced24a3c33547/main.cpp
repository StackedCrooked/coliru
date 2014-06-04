#include <iostream>
#include <queue>
#include <vector>
#include <boost/heap/binomial_heap.hpp>

struct item
{
    int _a; // weight
	int _p; // 
};

struct ratio_order
{
   bool operator()(const item* i1, const item* i2) const
   { return i1->_a * i2->_p < i2->_a * i1->_p; }
};

int main(int argc, char const *argv[])
{
	std::vector<item> items {{4,2}, {10,3}, {20, 4}, {7,2}};
    std::priority_queue<item*, std::vector<item*>, ratio_order> PQ;
    using Bpq_t = boost::heap::binomial_heap<item*, boost::heap::compare<ratio_order> >;
    //typedef typename boost::heap::binomial_heap<item*, boost::heap::compare<ratio_order> > Bpq_t; 
    //using bh_t = Bpq_t::handle_type;
    typedef typename Bpq_t::handle_type bh_t;
    Bpq_t Bpq;
    std::vector<bh_t> it_handlers;

	for (auto& i : items) {
		std::cout << "(" << i._a << ", " << i._p << ")  ";
        PQ.push(&i);
        auto bh = Bpq.push(&i);
        it_handlers.push_back(bh);
	}
    std::cout << '\n';

    items[2]._a = 13; // modified
    auto bh = it_handlers[2];
    Bpq.update(bh);

	while (!PQ.empty()) {
		item* ip = PQ.top(); 
		std::cout << "(" << ip->_a << ", " << ip->_p << ")  ";
		PQ.pop();
	}
	std::cout << '\n';

	while (!Bpq.empty()) {
		item* ip = Bpq.top(); 
		std::cout << "(" << ip->_a << ", " << ip->_p << ")  ";
		Bpq.pop();
	}
	std::cout << '\n';

	return 0;
}