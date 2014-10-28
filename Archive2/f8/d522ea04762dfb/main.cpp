#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

using namespace std::literals::chrono_literals;

/**
 * @brief deWitters fixed flexible game loop
 * 
 * This game loop by deWitter calls update with a fixed rate of 
 * UpdatesPerSecond and handles input + renders as often as possible,
 * with a max frame skip.
 * The rendering-function should take a float as parameter, which
 * indicates how much of the time between the updates has already passed.
 * 
 * @tparam UpdatesPerSecond Set the number of updates per second, default is 25
 * @tparam MaxFrameSkip Set the max number of frames that may be skipped if updates take too long, default is 5
 * 
 * @param handle_input Callable for handling input
 * @param update Callable for doing the actual update
 * @param render Callable for rendering. This should take a float as parameter
 * @param state Callable to check if the gameloop as to continue running. This should true to keep running, false otherwise
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

    while(state()) {
        handle_input();

    	for(auto loops = decltype(MaxFrameSkip){0};
			loops < MaxFrameSkip && clock_type::now() > next_game_tick;
			++loops, next_game_tick += update_delta)
        {
            update();
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
