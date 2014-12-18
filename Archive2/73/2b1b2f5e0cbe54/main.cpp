#include <iostream>
#include <tuple>
#include <memory>
#include <utility>
using namespace std;

// this class allows user to call "run" without any args 
class simulation_base{
public:
    int run(){ return execute_simulation_wrapped(); }; 
protected:
    virtual int execute_simulation_wrapped() {return 0;};
};

// this class funnels some stored inputs into a soon-to-be-overridden method
template <typename... Ts>
struct simulation_wrapper : public simulation_base {
    tuple<shared_ptr<Ts>... > stored_inputs{new Ts...};

    public:
    int execute_simulation_wrapped() { return execute_simulation_wrapped(std::make_index_sequence<sizeof...(Ts)>{}); }
    
    private:
    template <std::size_t... Is>
    int execute_simulation_wrapped(std::index_sequence<Is...>) { return simulation(*std::get<Is>(stored_inputs)...); }

    protected:
    virtual int simulation(Ts...){return 0;};
};

struct woman{};
struct girl{};
struct cat{};
struct man{};
struct dog{};

struct jones_household : public simulation_wrapper< woman, girl, cat >{
    int simulation(woman mrs_jones, girl mary, cat sniffles) {
         // mrs_jones and her daugther mary play with sniffles the cat
         std::cout << "int simulation(woman mrs_jones, girl mary, cat sniffles)\n";
         return 1;
    }
};

struct smith_household : public simulation_wrapper< man, dog >{
    int simulation(man mr_smith, dog fido) {
         // mr_smith and his dog fido go for a walk
         std::cout << "int simulation(man mr_smith, dog fido)\n";
         return 1;
    }
};

void play_simulation(simulation_base& some_household){
     // do some general stuff
     some_household.run(); 
}

int main()
{
    smith_household uinverse_1_smiths;
    smith_household uinverse_2_smiths;
    jones_household uinverse_1_jones;
    jones_household uinverse_2_jones;
    
    play_simulation(uinverse_1_smiths);
    play_simulation(uinverse_2_smiths);
    play_simulation(uinverse_1_jones);
    play_simulation(uinverse_2_jones);
}
