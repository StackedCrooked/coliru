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

class Warrior : NonCopyable {
public:
  Warrior(uint id, std::string name)
      : _id{id},
        _name{std::move(name)}
  { }

  std::string getName() const { return _name; }
  int getId() const { return _id; }
  bool isAlive() const { return _alive; }
  
private:

  uint _id;
  std::string _name;

    bool _alive = true;

public:
  Warrior(Warrior&& that)
      : _id{that._id}, _name{std::move(that._name)}
  { }
};

class VM {
public:
  VM()
      : _warriors{std::vector<Warrior>()}
  { }

  void addWarrior(char const* filename);
  
  std::vector<Warrior>& getWarriors();
  auto getAlive();

  long countAlive() const;
private:
  std::vector<Warrior> _warriors;
  uint _last_id = 0;
};

void VM::addWarrior(char const* name) {
    _warriors.emplace_back(_last_id++, name);
}


std::vector<Warrior>&
VM::getWarriors()
{
  return _warriors;
}

auto
VM::getAlive()
{
  return _warriors | filtered(std::mem_fn(&Warrior::isAlive));
}

int main() {
    VM myvm;
    myvm.addWarrior("one");
    myvm.addWarrior("wot");
    myvm.addWarrior("thrr");
    myvm.addWarrior("four");
    for (auto&& w : myvm.getAlive()) {
        std::cout << w.getName() << "\n";
    }
}