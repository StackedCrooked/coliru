#include <boost/heap/fibonacci_heap.hpp>
#include <iostream>
#include <random>

namespace {
    std::discrete_distribution<int> dist({1,1,1,1,1,1});
    static auto price_gen = [&] { 
        static std::mt19937 rng;
        static double values[] = {52.40, 12.30, 87.10, 388., 0.10, 23.40};
        return values[dist(rng)]; 
    };
}

struct Order {
    double price      = price_gen();
    unsigned quantity = rand() % 4 + 1;

    double subtotal() const { return price * quantity; }

    bool operator<(Order const& other) const { return subtotal() < other.subtotal(); }
};

using Heap = boost::heap::fibonacci_heap<Order>;

struct Y {
    virtual void printSnapshot(std::ostream &ss) {
        //Heap cloned(static_cast<Heap const&>(this->heap));
        Heap cloned(this->heap); // CORRUPTS THE SOURCE HEAP
        double prev_price = std::numeric_limits<double>::max();

        while (cloned.size() > 0) {
            const Order &order = cloned.top();

            if (order.price != prev_price) {
                if (prev_price != std::numeric_limits<double>::max())
                    ss << std::endl;
                ss << order.price << " | ";
            }
            ss << order.quantity << " ";
            prev_price = order.price;
            cloned.pop();
        }
        ss << std::endl;
    }

    void generateOrders() {
        for (int i=0; i<3; ++i) {
            heap.push({});
        }
    }

    Heap heap;
};

int main() {
    Y y;
    for(int i=0; i<10; ++i) {
        y.generateOrders();
        y.printSnapshot(std::cout);
    }
}
