#include <iostream>
#include <utility>
#include <string>

class Person
{
public:
        Person(const std::string first, const std::string second) :
                firstname{std::move(first) }, secondname{ std::move(second) } {}

        Person() = default;

        //      Less_than operator
        bool operator<(const Person& p) const
        {
                return(secondname < p.secondname ||
                        ((secondname == p.secondname) && (firstname < p.firstname)));
        }

        //      Greater_than operator
        bool operator>(const Person& p) const
        {
                return p < *this;
        }

        //      Output a person
        void showPerson() const
        {
                std::cout << firstname << " " << secondname << std::endl;
        }

private:
        std::string firstname;
        std::string secondname;
};

#include <vector>
#include <queue>
#include <functional>

int main()
{
        std::priority_queue<Person, std::vector<Person>, std::greater<>> people;
        std::string first, second;
        while (true)
        {
                std::cout << "Enter a first name or press Enter to end: ";
                std::getline(std::cin, first);
                if (first.empty())
                        break;


                std::cout << "Enter a second name: ";
                std::getline(std::cin, second);
                people.push(Person{ first, second });
        }

        std::cout << "\nThere are " << people.size() << " people in the queue."
                << std::endl;

        std::cout << "\nThe names that you entered are : " << std::endl;
        while (!people.empty())
        {
                people.top().showPerson();
                people.pop();
        }

        if (people.empty())
                std::cout << "Priority queue is empty! " << std::endl;

        return 0;
}
