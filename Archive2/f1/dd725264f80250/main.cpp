#include <map>

class Foobar
{
public:

    enum class Lecture
    {
        COMP_SCI,
        PHYSICS,
        CHEMISTRY,
        BIOLOGY,
        PSYCHOLOGY,
        MODERN_ART
        PHILOSOPHY,
        SOCIOLOGY
    };

    enum class Day
    {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };
};

int main() {
    std::map<Foobar::Lecture, Foobar::Day> lectureToDayMap;   
}