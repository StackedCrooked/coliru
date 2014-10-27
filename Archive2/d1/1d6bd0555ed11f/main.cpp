#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

using namespace std::literals::chrono_literals;

/**
 * deWitters fixed flexible game loop
 *
 * This game loop by deWitter calls update with a fixed
 * rate of UpdatesPerSecond and handles input+renders as often as possible,
 * with a max frame skip.
 */
template<std::size_t UpdatesPerSecond = 25,
         std::size_t MaxFrameSkip = 5,
         class InputFunc,
         class UpdateFunc,
         class RenderFunc,
         class StateFunc
         >
void dewitters_gameloop(InputFunc&& handle_input, UpdateFunc&& update, RenderFunc&& render, StateFunc&& state)
{
    using clock_type = std::chrono::steady_clock;
    using update_delta_type = std::chrono::duration<float, std::ratio<1,UpdatesPerSecond>>;

    constexpr auto update_delta = update_delta_type{1};
    std::chrono::time_point<clock_type, update_delta_type> next_game_tick = clock_type::now();

    auto loops = std::size_t{};

    while(state()) {
        handle_input();

		loops = 0;
		while(loops < MaxFrameSkip
			  && clock_type::now() > next_game_tick)
        {
            update();

            next_game_tick += update_delta;
            loops++;
        }

		render(update_delta_type{
				   update_delta
				   + clock_type::now()
				   - next_game_tick}.count()
			   );
	}
}


class engineding
{
public:
    void input() { std::cout << "-- input()\n"; work(); }
    void update() {std::cout << "## update()\n"; ++counter; work(); }
    void render(float d) { std::cout << "|| render(" << d << ")\n"; work(); }
    bool state() { return (counter < 20) ? true : false; }
private:
    std::size_t counter;
    void work() { std::this_thread::sleep_for(5ms); }
};

int main()
{
    engineding e{};
    
    dewitters_gameloop<20,7>(
        std::bind(&engineding::input, &e),
        std::bind(&engineding::update, &e),
        std::bind(&engineding::render, &e, std::placeholders::_1),
        std::bind(&engineding::state, &e)
        );
        
    std::cout << "bye." << std::endl;
    
    return 0;
}
