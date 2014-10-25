#include <queue>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>

using namespace std;

template <class T, class Container = vector<T>>
using lowest_priority_queue = priority_queue<T, Container, greater<T>>;

enum class node_state { unvisited, waiting, visited };

template <class, class>
struct node;

template <class T, class U>
struct adjacent {
    reference_wrapper<node<T, U>> node;
	U cost;
};

template <class T, class U>
struct route_node {
	node<T, U> *node;
	U cost = 0;
	shared_ptr<route_node> next = nullptr;
};

template <class T, class U>
using route = shared_ptr<route_node<T, U>>;

template <class T, class U>
bool operator>(const route<T, U> &lhs, const route<T, U> &rhs) {
	return lhs->cost > rhs->cost;
}

template <class T, class U>
route<T, U> operator+(const route<T, U> &lhs, const adjacent<T, U> &rhs) {
	return make_shared<route_node<T, U>>(
	    route_node<T, U>{&rhs.node.get(), lhs->cost + rhs.cost, lhs});
}

template <class T, class U>
struct node {
	node(const T &key) : key(key) {
	}

	T key;
	vector<adjacent<T, U>> adjacents;
	node_state state = node_state::unvisited;
};

using string_node = node<const char *, int>;
using string_route_node = route_node<const char *, int>;
using string_route = route<const char *, int>;

ostream &operator<<(ostream &os, const string_route &r) {
	if (r == nullptr)
		return os;
	os << r->cost << "\t| " << r->node->key;
	for (auto it = &r->next; *it != nullptr; it = &(*it)->next)
		os << " <- " << (*it)->node->key;
	return os << endl;
}

template <class F>
void dijkstra(string_node &n, F f) {
	lowest_priority_queue<string_route> pq;
	n.state = node_state::waiting;
	pq.push(make_shared<string_route_node>(string_route_node{&n}));
	while (!pq.empty()) {
		auto top = pq.top();
		auto &front = *top->node;
		pq.pop();
		if (front.state != node_state::visited) {
			front.state = node_state::visited;
			if (f(top))
				break;
			for (adjacent : front.adjacents) {
				auto &adjacent_state = adjacent.node.get().state;
				if (adjacent_state != node_state::visited) {
					adjacent_state = node_state::waiting;
					pq.push(top + adjacent);
				}
			}
		}
	}
}

int main() {
	string_node a{"a"}, b{"b"}, c{"c"}, d{"d"}, e{"e"}, f{"f"}, g{"g"}, h{"h"},
	    i{"i"};
	a.adjacents = {{b, 7}, {c, 4}, {d, 5}};
	b.adjacents = {{a, 7}, {c, 2}, {e, 25}};
	c.adjacents = {{a, 4}, {b, 2}, {h, 9}};
	d.adjacents = {{a, 5}, {f, 9}};
	e.adjacents = {{b, 25}, {g, 10}};
	f.adjacents = {{d, 9}, {h, 20}};
	g.adjacents = {{e, 10}, {i, 2}};
	h.adjacents = {{c, 9}, {f, 20}, {i, 3}};
	i.adjacents = {{g, 2}, {h, 3}};

	dijkstra(a, [](auto &route) {
		cout << route;
		return false;
	});
}