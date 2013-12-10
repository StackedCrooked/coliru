#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct student
{
    std::string first_name ;
    std::string last_name ;
    std::string credits ;
    std::string gpa ;
    std::string first_date ;
    std::string second_date ;
};

constexpr char delimiter = '|' ;

bool to_student( const std::string& line, student& s )
{
    std::istringstream stm(line) ;

    if( std::getline( stm, s.first_name, delimiter ) &&
        std::getline( stm, s.last_name, delimiter ) &&
        std::getline( stm, s.credits, delimiter ) &&
        std::getline( stm, s.gpa, delimiter ) &&
        std::getline( stm, s.first_date, delimiter ) &&
        std::getline( stm, s.second_date ) ) return true ;

    s = student() ;
    return false ;
}

struct course
{
    std::string course_name ;
    std::string course_code ;
    std::string number_of_credits ;
    std::string professor_name ;
    std::vector<student> students ;
};

bool to_course( const std::string& line, course& c )
{
    std::istringstream stm(line) ;

    if( std::getline( stm, c.course_name, delimiter ) &&
        std::getline( stm, c.course_code, delimiter ) &&
        std::getline( stm, c.number_of_credits, delimiter ) &&
        std::getline( stm, c.professor_name, delimiter ) ) return true ;

    c = course() ;
    return false ;
}

int main()
{
    std::istringstream text_file
    (
        "algorithms|CS104|5|DE Knuth\n"
        "Andrei|Tarkovsky|5|25|01/12/2013|31/03/2014\n"
        "Yasujiro|Ozu|4.5|22.5|01/12/2013|31/03/2014\n"
        "end_roster|\n"
        "metaprogramming|CS201|4|Dave Abrahams\n"
        "Ingmar|Bergman|4.7|18.8|01/12/2013|31/03/2014\n"
        "Bela|Tarr|4.5|18|01/12/2013|31/03/2014\n"
        "Krzysztof|Kieslowski|4.6|18.4|01/12/2013|31/03/2014\n"
        "end_roster|\n"
    );

    std::vector<course> roster ;

    std::string line ;
    while( std::getline( text_file, line ) )
    {
        course c ;
        if( to_course( line, c ) )
        {
            student s ;
            while( std::getline( text_file, line ) && to_student( line, s ) )
                c.students.push_back(s) ;
        }
        roster.push_back(c) ;
    }

    for( const course& c : roster )
    {
        std::cout << c.course_code << ' ' << c.course_name << ": "
                   << c.professor_name << '\n' ;

        for( const student& s : c.students )
            std::cout << "    " << s.first_name << ' ' << s.last_name << '\n' ;

        std::cout << '\n' ;
    }
}
