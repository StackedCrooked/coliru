#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using name_t = std::pair<std::string,std::string> ;

struct student
{
    name_t name_ ;
    int age_ ;

    std::string name() const { return name_.second + ", " + name_.first ; }
    int age() const { return age_ ; }
};

int main()
{
    using student_container_t = std::vector<student> ;

    student_container_t student_container =
    {
        { { "Stan", "Lippman" }, 21 },
        { { "Bjarne", "Stroustrup" }, 20 },
        { { "Andrew", "Koenig" }, 23 },
        { { "Jerry", "Schwartz" }, 19 },
        { { "Jim", "Coplien" }, 22 }
    };

    // sort on name
    std::sort( std::begin(student_container), std::end(student_container),
                []( student a, student b ) { return a.name() < b.name() ; } ) ;

    std::cout << "sorted on name\n--------------\n" ;
    for( student s : student_container )
        std::cout << s.name() << ' ' << s.age() << '\n' ;

    // sort on age
    std::sort( std::begin(student_container), std::end(student_container),
                []( student a, student b ) { return a.age() < b.age() ; } ) ;

    std::cout << "\nsorted on age\n--------------\n" ;
    for( student s : student_container )
        std::cout << s.age() << ' ' << s.name() << '\n' ;
}
