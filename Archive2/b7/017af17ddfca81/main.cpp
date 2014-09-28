#include <cassert>
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

// something to simulate, the game of life
struct GoL {
  enum State { dead, live };

  const int columns = 25;
  const int rows = 25;
  std::vector<State> v = std::vector<State>(columns * rows, dead);

  State &access(int column, int row) {
    row = std::abs(row % rows);
    column = std::abs(column % columns);
    assert(0 <= column && column < columns && 0 <= row && row < rows);
    return v[row * columns + column];
  }

  State const &access(int column, int row) const {
    return const_cast<GoL *>(this)->access(column, row);
  }

  GoL &tick() {
    GoL copy = *this;

    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < columns; ++col) {
        int live_neighbors =
            copy.access(col - 1, row - 1) + copy.access(col, row - 1) +
            copy.access(col + 1, row - 1) + copy.access(col - 1, row) +
            copy.access(col + 1, row) + copy.access(col - 1, row + 1) +
            copy.access(col, row + 1) + copy.access(col + 1, row + 1);

        if (live == copy.access(col, row) &&
            (live_neighbors == 2 || live_neighbors == 3)) {
          access(col, row) = live;
        } else if (dead == copy.access(col, row) && live_neighbors == 3) {
          access(col, row) = live;
        } else {
          access(col, row) = dead;
        }
      }
    }
    return *this;
  }

  GoL &randomize() {
    std::mt19937 eng;
    std::binomial_distribution<> dist;

    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < columns; ++col) {
        access(col, row) = dist(eng) ? live : dead;
      }
    }
    return *this;
  }

  GoL() = default;
  GoL(int rows_, int columns_) : columns(columns_), rows(rows_) {}
  GoL(GoL const &gol) = default;
};

static std::ostream &operator<<(std::ostream &os, GoL const &rhs) {
  for (int row = 0; row < rhs.rows; ++row) {
    for (int col = 0; col < rhs.columns; ++col) {
      os << (rhs.access(col, row) == GoL::live ? "# " : "  ");
    }
    os << "\n";
  }
  return os;
}

// a simple, thread-safe queue
template <typename T, int N> class Event_queue {
  static constexpr int max_events = N;

  std::mutex event_mutex;
  int events = 0;
  T event_buffer[N];

public:
  Event_queue() = default;

  void add_event(T e) {
    std::lock_guard<std::mutex> _(event_mutex);
    if (events < max_events) {
      event_buffer[events] = e;
      ++events;
    }
  }

  template <typename Handler> void get_events(Handler handler) {
    std::lock_guard<std::mutex> _(event_mutex);
    for (int i = 0; i < events; ++i) {
      handler(event_buffer[i]);
    }
    events = 0;
  }
};

enum Event { quit_request, show_request };

// simulation will check for user input each tick
static void simulation(Event_queue<Event, 5> &queue) {
  GoL game;
  game.randomize();

  bool quit = false;
  while (!quit) {
    game.tick();

    queue.get_events([&](Event e) {
      switch (e) {
      case quit_request:
        quit = true;
        return;
      case show_request:
        std::cout << game << '\n';
        break;
      }
    });
  }
}

int main() {
  // mechanism to communicate user input to simulation thread
  Event_queue<Event, 5> queue;

  // run simulation on background thread
  std::future<void> game =
      std::async(std::launch::async, simulation, std::ref(queue));

  // loop to get user input, put user input into thread-safe queue
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "quit") {
      queue.add_event(quit_request);
      game.get();
      return EXIT_SUCCESS;
    } else if (line == "print") {
      queue.add_event(show_request);
    } else {
      std::cerr << "error: command not understood.\n";
    }
  }
}
