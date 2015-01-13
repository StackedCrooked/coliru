#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <set>

struct Student
{
    std::string studentName;
    int midTermScore;
    char grade;

    friend bool operator<(Student const & a, Student const & b)
    {
        return a.midTermScore > b.midTermScore;
    }
};

template<typename C>
void display(const C& c)
{
    std::cout << std::left 
        << std::setw(10) << " Names"
        << std::setw(10) << "Exam" 
        << std::setw(10) << "Grade";

    std::cout << std::setfill('-') << std::setw(28) << '\n';

    for (const auto& i : c)
    {
        std::cout << "\n " << std::setfill(' ') << std::left
            << std::setw(10) << i.studentName
            << std::setw(11) << i.midTermScore
            << std::setw(2) << i.grade;
    }
}

int main()
{
    std::array<Student, 4> a
    {
        {
            { "me",     60, 'D'},
            {"matt",    88, 'B'},
            { "john",   93, 'A'},
            {"jesseca", 60, 'B'}

        }
    };

    display(a);

    std::set<Student> sorted;

    for (auto&& i : a)
    {
        sorted.insert(i); // O(N*log(size() + N))
    }

    std::cout << "\n\nafter sorting\n\n";

    display(sorted);
}