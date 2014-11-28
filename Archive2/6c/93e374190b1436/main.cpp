#include <iostream>
#include <vector>
#include <memory>

class Table {

  public:
    struct Listener{ 
      virtual void handle(int i) = 0;
    };

    std::vector<std::unique_ptr<Listener>> listeners_;

    void add_listener(std::unique_ptr<Listener> l){
      listeners_.push_back(std::move(l));
    }

};


struct EventListener: public Table::Listener {
  void handle(int e){  
    std::cout << "Something happened! " << e << " \n";
  }
};

int main(int argc, char** argv)
{
  Table table;
  std::unique_ptr<EventListener> el;
  table.add_listener(std::move(el));

  return 0;
}