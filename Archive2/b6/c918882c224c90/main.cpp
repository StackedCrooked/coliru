#include <algorithm>
#include <vector>
#include <memory>

struct Base {
    virtual double stuff(double) { return 0; }
};

struct Threes : Base {
    virtual double stuff(double) { return 3; }
};

struct Sevens : Base {
    virtual double stuff(double) { return 7; }
};

std::vector<double> vstuff(double t, std::vector<std::shared_ptr<Base> > things)
{
    std::vector<double> vals;
    vals.resize(things.size());
    transform(things.begin(), things.end(), vals.begin(), std::bind(&Base::stuff, std::placeholders::_1, t));
    return vals;
}

#include <iostream>

int main() {
    for (double v : vstuff(42, {
                std::make_shared<Sevens>(),
                std::make_shared<Sevens>(),
                std::make_shared<Sevens>(),
                std::make_shared<Threes>(),
                std::make_shared<Sevens>(),
                std::make_shared<Threes>(),
                std::make_shared<Sevens>(),
                std::make_shared<Sevens>(),
                std::make_shared<Threes>(),
                std::make_shared<Sevens>(),
            }))
    {
        std::cout << v << " ";
    }
}
