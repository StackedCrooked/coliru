#include <string>
#include <iostream>

class Staff {
public:
    long int staffId_;
    std::string nickname_;
};

template <typename Derived, typename MemberType>
class ColumnObject {
public:
    MemberType Derived::*memberPtr_;
    char const *columnName_;
    int const traits_;
    int columnNumber_;

    constexpr ColumnObject()
        : memberPtr_(nullptr),
          columnName_("UNITIALIZED COLUMN"),
          traits_(-1),
          columnNumber_(-1) {
    }

    constexpr ColumnObject(MemberType Derived::*memberPtr,
                           char const *columnName,
                           int const traits)
        : memberPtr_(memberPtr),
          columnName_(columnName),
          traits_(traits),
          columnNumber_(-1) {
    }
};

int main() {
    static constexpr auto colTest1 =
        ColumnObject<Staff, long int>(&Staff::staffId_,
                                      "staff_id",
                                      0);
    static constexpr auto colTest2 =
        ColumnObject<Staff, std::basic_string<char>>(
            &Staff::nickname_, "nick_name", 0);

    std::cout << colTest1.memberPtr_ << std::endl;
    std::cout << colTest2.memberPtr_ << std::endl;
}