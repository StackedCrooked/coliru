#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>

struct Student_average {
  int student_id;
  float average;
};

bool compare_student_averages(Student_average const &lhs,
                                     Student_average const &rhs) {
  return lhs.average < rhs.average;
}

int main() {
  std::vector<Student_average> averages;

  // collect the data and populate the averages vector
  averages.insert(end(averages),
      {{1, 0.9f}, {2, 0.5f}, {3, 0.7f}, {4, 0.5f}, {5, 0.8f}}); // dummy data

  sort(begin(averages), end(averages), compare_student_averages);

  std::cout << "The worst average is: " << averages.front().average << '\n';

  auto end_of_worst_student_averages =
      upper_bound(begin(averages), end(averages), averages.front(),
                  compare_student_averages);

  std::cout << "The IDs of the students with the worst averages are:\n";

  transform(begin(averages), end_of_worst_student_averages,
            std::ostream_iterator<int>(std::cout, "\n"),
            std::mem_fn(&Student_average::student_id));
}

