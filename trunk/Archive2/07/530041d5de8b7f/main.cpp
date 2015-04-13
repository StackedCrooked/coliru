#include <iostream>
#include <vector>
#include <chrono>
using ratio = std::ratio<60 * 60 * 24, 1>;
using time_point = std::chrono::system_clock::time_point;
using days_t = std::chrono::duration<time_point::rep, ratio>;

struct Expedition {
  int x = 0;
  int y = 0;
  std::string who;
  std::string how;
  std::string why;
  days_t days;
};

void do_expedition(std::vector<Expedition>& expeditions, const std::string& who,
                   int x, int y, const std::string& why, days_t days,
                   const std::string& how = "walking")
{
  expeditions.emplace_back(Expedition{ x, y, who, how, why, days });
  std::cout << who << " has gone on an expedition to " << x << "," << y
            << " by " << how << " because they are " << why << " for "
            << days.count() << " days." << std::endl;
}

int main() {
  std::vector<Expedition> expeditions;
  do_expedition(expeditions, "scientist", 1, 1, "investigating native lifeforms",
                std::chrono::duration_cast<days_t>(std::chrono::minutes(3 * 60 * 24)));
  do_expedition(expeditions, "engineer", 1, 2, "constructing power supply",
                std::chrono::duration_cast<days_t>(std::chrono::hours(2 * 24)));
  do_expedition(expeditions, "soldier", 2, 3, "securing territory",
                days_t(1));
  return 0;
}