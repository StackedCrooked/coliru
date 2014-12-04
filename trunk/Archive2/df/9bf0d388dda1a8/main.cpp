template<class T> struct sc_in {};
template<class T> struct sc_out {};
struct sc_module {
    sc_module(const char*){}
};
#define SC_MODULE(X) class X : public sc_module
#define SC_HAS_PROCESS(X) int has_process
#define SC_METHOD(X) X();
using sc_module_name = char*;





#include <vector>

#define ROBOT_SPEED 0.1

SC_MODULE (Robot)
{
private:
  std::vector<unsigned> path;
public:
  sc_in<bool> clk;          // system clock
  sc_in<bool> canMove;      // true = safe to move
  sc_in<unsigned> position; // current position

  sc_out<bool> arrived;     // true =  arrived at next position

  SC_HAS_PROCESS(Robot);
  Robot(sc_module_name name_, std::vector<unsigned> path);

  void prc_robot();
};


SC_MODULE (Server)
{
public:
  sc_in<bool> clk;

  SC_HAS_PROCESS(Server);
  Server(sc_module_name name_, std::vector<Robot> robots);

  void prc_server();
};

Server::Server(sc_module_name name_, std::vector<Robot> robots) : sc_module(name_)
{
  SC_METHOD(prc_server);
    //sensitive << clk.pos();
}


void Server::prc_server()
{

}

Robot::Robot(sc_module_name name_, std::vector<unsigned> path) : sc_module(name_)
{
  this->path = path;

  SC_METHOD(prc_robot);
    //sensitive<<clk.pos();
}

void Robot::prc_robot()
{

}

int main() {
}