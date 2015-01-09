#include <string>

// QUIZ: Constructor inheritance!

// Which of the following classes will fail to compile?

struct a : std::string { using string::string; };
struct b : std::string { using std::string::string; };
struct c : std::string { using basic_string::basic_string; };
struct d : std::string { using std::basic_string::basic_string; };
