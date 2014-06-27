#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <cassert>

struct Student
{
    int average;
    int get_average() const { return average; }
    
    bool operator<(Student const& other) const
    { return get_average() < other.get_average(); }
    
    bool operator>(Student const& other) const
    { return get_average() > other.get_average(); }
};

Student lowest_grade(const std::vector<Student> &all_students){
  return *std::min_element(std::begin(all_students), std::end(all_students),
      [](const Student &a, const Student &b){
    return a.get_average() < b.get_average();});
}

Student highest_grade(const std::vector<Student> &all_students){
  return *std::max_element(std::begin(all_students), std::end(all_students),
      [](const Student &a, const Student &b){
    return a.get_average() < b.get_average();});
}

template<typename Func>
Student dispatch(const std::vector<Student> &all_students, Func func)
{
    assert(!all_students.empty());
    return *func(std::begin(all_students), std::end(all_students), 
                 [](const Student &a, const Student &b){return a.get_average() < b.get_average();});
}

template<typename Func>
Student dispatch2(const std::vector<Student> &all_students, Func func)
{
    assert(!all_students.empty());
    return *func(std::begin(all_students), std::end(all_students));
}

template<typename Comparator>
Student dispatch3(const std::vector<Student> &all_students, Comparator comp)
{
    assert(!all_students.empty());
    return *std::min_element(std::begin(all_students), std::end(all_students), comp);
}

int main()
{
  std::vector<Student> students{Student{20}, Student{10}, Student{40}, Student{30}};
  
  std::cout << "Lowest: " << lowest_grade(students).average << '\n';
  std::cout << "Highest: " << highest_grade(students).average << '\n';

  std::cout << "Lowest: " << dispatch(students, 
                                      std::min_element<decltype(students)::const_iterator, bool(*)(const Student&, const Student&)>).average << '\n';
  std::cout << "Highest: " << dispatch(students, 
                                       std::max_element<decltype(students)::const_iterator, bool(*)(const Student&, const Student&)>).average << '\n';
                                       
  std::cout << "Lowest: " << dispatch2(students, 
                                      std::min_element<decltype(students)::const_iterator>).average << '\n';
  std::cout << "Highest: " << dispatch2(students, 
                                       std::max_element<decltype(students)::const_iterator>).average << '\n';
                                       
  std::cout << "Lowest: " << dispatch3(students, std::less<Student>()).average << '\n';
  std::cout << "Highest: " << dispatch3(students, std::greater<Student>()).average << '\n';
  
  auto minmax = std::minmax_element(std::begin(students), std::end(students));
  std::cout << "Lowest: " << minmax.first->average << '\n';
  std::cout << "Highest: " << minmax.second->average << '\n';
}
