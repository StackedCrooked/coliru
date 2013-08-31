#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

struct IdObject
{
    typedef unsigned long Id;
    Id id;
    IdObject() : id([]{ static auto id_gen = 0ul; return ++id_gen; }()) { }

    Id getId() const { return id; }
    virtual ~IdObject() {}
};

template <
    typename C, 
    typename V = typename C::value_type,
    typename Id=decltype(std::declval<V>().getId())
    > V* findById(C& collection, Id id)
{
    auto match = std::find_if(
            begin(collection), end(collection), 
            [id](V const& v) { return id == v.getId(); });

    return (match == end(collection))? nullptr : &*match;
}

template <typename C>
std::string IdList(C const& collection)
{
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for(auto& i: collection)
    {
        oss << (first?"":", ") << i/*.getId()*/;
        first = false;
    }
    oss << "}";
    return oss.str();
}

struct Person : IdObject
{
    std::string firstname, surname;
    Person(std::string firstname, std::string surname)
        : firstname(std::move(firstname)), surname(std::move(surname))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, Person const& p) {
        return os << "Person { id=" << p.id << ", firstname=" << p.firstname << ", surname=" << p.surname << "}";
    }
};

struct Course : IdObject
{
    std::string courseName;
    std::set<Course::Id> preCourses;

    Course(std::string courseName, std::set<Course::Id>&& preCourses = {}) : 
        courseName(std::move(courseName)),
        preCourses(std::move(preCourses))
        {
        }

    Id getCourseId() const { return id; }
    std::set<Course::Id> const& getPreCourses() const { return preCourses; }
    std::string const& getCourseName() const { return courseName; }

    friend std::ostream& operator<<(std::ostream& os, Course const& c) {
        return os << "Course '" << c.courseName << "', id=" << c.getCourseId() << ", req=" << IdList(c.getPreCourses());
    }
};

struct Student : Person
{
    Student(std::string firstname, std::string surname)
        : Person(std::move(firstname), std::move(surname))
    {
    }

    std::list<Course::Id> signedCourses;
    std::list<Course::Id>& getSignedCourse() { return signedCourses; } 

    friend std::ostream& operator<<(std::ostream& os, Student const& p) {
        return os << "Student { Person=" << ((Person&) p) << ", signedCourses=" << IdList(p.signedCourses) << "}";
    }
};

struct Teacher : Person
{
    Teacher(std::string firstname, std::string surname)
        : Person(std::move(firstname), std::move(surname))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, Teacher const& p) {
        return os << "Teacher { Person=" << ((Person&) p) << "}";
    }
};

struct Menu
{
    std::vector<std::string> entries;

    Menu(std::initializer_list<std::string> entries)
        : entries(entries) {}

    int choose() const {
        std::cout << "Choose from the list: \n";
        int choice = 0;
        for (auto& entry : entries)
            std::cout << (choice++) << "\t" << entry;
        std::cout << "Choice: ";
        std::cin.clear();
        return (std::cin >> choice)? choice : -1;
    };
};

struct App
{
    App();
    void Run();
    void studentsMenu(unsigned long);
    void teachersMenu(unsigned long);

    std::vector<Menu> appMenu;
    std::list<Student> studentsList;
    std::list<Teacher> teachersList;
    std::list<Course> coursesList;
};

App::App()
{
    appMenu = {
        { // Students menu init
            "Print all the information for all the courses \n",
            "Print all the information for all the tests  \n",
            "Register to course \n",
            "Get a pdf name of a test \n",
            "Exit \n",
        },
        {
            // Teachers menu init
            "Moving test to the database \n",
            "Updating students grades  \n",
            "Print student info \n",
            "Exit \n",
        }
    };

    studentsList = { { "zachi","kfar monash" } };
    teachersList = { { "ori","beit halevi" } };
    coursesList.emplace_back("Hedva");
    coursesList.emplace_back("Hedva B", std::set<Course::Id> { coursesList.front().getCourseId() });

    studentsList.front().getSignedCourse().push_back(coursesList.front().getCourseId());
}

void App::Run()
{
    for(auto const& c : coursesList)  std::cout << c << "\n";
    for(auto const& t : teachersList) std::cout << t << "\n";
    for(auto const& s : studentsList) std::cout << s << "\n";
    
    int index=-1;
    unsigned long id;
    bool exist = false;

    while (!exist)
    {
        cout << "For student press 0 , for teacher press 1"<<endl;
        std::cin.clear();
        cin >> index;
        while ((index != 1) && (index != 0))
        {
            cout << "please enter a valid choice 0/1"<<endl;
            cin >> index;
        }
        cout << "Please enter your id: ";
        std::cin.clear();
        cin >> id;
        if (index == 0)
        {
            auto found = findById(studentsList, id);
            if (found)
            {
                exist = true;
                App::studentsMenu(id);
            }
            else cout<<"The id does not exist";
        }
        else
        {
            auto itr = findById(teachersList, id);
            if (itr)
            {
                exist = true;
                App::teachersMenu(id);
            }
            else cout<<"The id does not exist";
        }
    }
}

void App::studentsMenu(unsigned long id)
{
    unsigned int l_option = 0;
    while (l_option != 4)
    {
        l_option = appMenu[0].choose();
        auto found = findById(studentsList, id);

        switch( l_option)
        {
            case 0:      // printing all the courses data
                {
                for (auto id : found->getSignedCourse())
                    cout << *findById(coursesList, id) << "\n";
                break;
                }
            case 1:     //printing all the test
                for (auto id : found->getSignedCourse())
                    cout << *findById(coursesList, id) << "\n";
                break;
            case 2:     //registering to course
                {
                    cout << "Please enter the course number: ";
                    std::cin.clear();
                    unsigned long courseId;
                    cin >> courseId;
                    if (auto foundCourse = findById(coursesList, courseId))
                    {
                        const std::set<Course::Id> prerequisites(foundCourse->getPreCourses().begin(), foundCourse->getPreCourses().end());
                        const std::set<Course::Id> signedCourses(found->getSignedCourse().begin(), found->getSignedCourse().end());

                        std::set<Course::Id> not_signed;
                        std::set_difference(begin(prerequisites), end(prerequisites),
                                begin(signedCourses), end(signedCourses),
                                std::inserter(not_signed, end(not_signed)));

                        if (!not_signed.empty())
                            cout << "You cant register to this course, you do not meet the requirements";
                        else
                        {
                            found->getSignedCourse().push_back(foundCourse->getId());
                            cout << "You have been add to "<<foundCourse->getCourseName()<<endl;
                        }
                    } else
                    {
                        cout << "The course number does not exist";
                        break;
                    }
                break;
                }
            case 3:
                return;
        }
    }
}

void App::teachersMenu(unsigned long id)
{

}

int main()
{
    App app;
    app.Run();
}
