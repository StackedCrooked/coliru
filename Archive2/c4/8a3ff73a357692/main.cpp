struct context {
    // stuff to pass around to the state
    int& x;
};

struct state {
    const context& c;
    state(const context& c): c(c) {}
    virtual ~state() = default;
    virtual void do_stuff() = 0;
};

struct my_state : public state {
    using state::state;
    virtual void do_stuff() {
        c.x = 20;
    }
};

#include <memory>
#include <iostream>

int main() {
    int x = 4;
    std::unique_ptr<state> game_state(new my_state({ x }));
    std::cout << game_state->c.x << '\n';
    game_state->do_stuff();
    std::cout << game_state->c.x << '\n';
}
    