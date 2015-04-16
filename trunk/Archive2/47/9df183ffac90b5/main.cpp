#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

struct Person {
    std::string fullname;
    int age = -1;

    friend std::istream& operator>>(std::istream& is, Person& v) {
        std::cout << "Fullname: ";
        std::getline(is, v.fullname);
        std::cout << "Age: ";
        is >> v.age;
        return is.ignore(1024, '\n');
    };
    friend std::ostream& operator<<(std::ostream& os, Person const& v) {
        return os << v.fullname << ", " << v.age;
    };
};

template <typename F>
void bubblesort(std::vector<Person>& v, F f)
{
    using iterator = decltype(std::begin(v));

    auto begin = std::begin(v), end = std::end(v);

    while (end != begin) {
        iterator new_end = begin;

        for (iterator i = begin; std::next(i) != end; std::advance(i, 1)) {
            iterator next = std::next(i);

            if (f(*next) < f(*i)) {
                std::iter_swap(i, next);
                new_end = next;
            }
        }

        end = new_end;
    }
}

std::vector<Person> input();
void output(std::string const& caption, std::vector<Person> const& table);

int main()
{
    std::vector<Person> table = input();
    output("before sorting", table);

    bubblesort(table, std::mem_fn(&Person::fullname));
    output("by name", table);

    bubblesort(table, std::mem_fn(&Person::age));
    output("by age", table);
}

std::vector<Person> input()
{
    std::vector<Person> result;
    std::copy(std::istream_iterator<Person>(std::cin), {}, back_inserter(result));
    return result;
}

void output(std::string const& caption, std::vector<Person> const& table)
{
    std::cout << caption << ":\n";
    for (auto& p : table)
        std::cout << "\t" << p << "\n";
}
