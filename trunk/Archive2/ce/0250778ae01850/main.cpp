#include <boost/range/adaptors.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::adaptors;


class NonCopyable {
protected:
  NonCopyable() = default;

public:
  NonCopyable(NonCopyable const &) = delete;

  NonCopyable &operator=(const NonCopyable &) = delete;
};

class warrior : NonCopyable {
    int id;
    char const* name;
public:
    warrior(int id, char const* name) : id{id}, name{name}
    { }

    warrior(warrior&& that) : id{that.id}, name{that.name}
    { }

    std::string getName() const { return std::string(name); }

    bool isAlive() const {
        static bool val = true;
        return val = !val;
    }
};

class vm{
    std::vector<warrior> _warriors;
public:
    void addWarrior(int id, char const* name){
        warrior w{id, name};
        _warriors.emplace_back(std::move(w));
    }
    std::vector<warrior>& getWarriors() { return _warriors; }
    auto getAlive() const {
        return _warriors | filtered(std::mem_fn(&warrior::isAlive));
    }

    long countAlive() const { return boost::size(getAlive()); }
};

int main() {
    vm myvm;
    myvm.addWarrior(1,"one");
    myvm.addWarrior(2,"wot");
    myvm.addWarrior(3,"thrr");
    myvm.addWarrior(4,"four");
    for (auto&& w : myvm.getAlive()) {
        std::cout << w.getName() << "\n";
    }
}