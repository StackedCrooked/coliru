#include <string>

template <typename Derived, typename MemberType>
class ColumnObject;

template <typename Derived, typename MemberType>
class ColumnObject {
public:
    MemberType Derived::*memberPtr_;
    char const *columnName_;

    constexpr ColumnObject()
        : memberPtr_(nullptr), columnName_("UNITIALIZED COLUMN") {
    }

    constexpr ColumnObject(MemberType Derived::*memberPtr,
                           const char *columnName)
        : memberPtr_(memberPtr), columnName_(columnName) {
    }
};

class Staff {
public:
    long int staffId_;
    std::string nickname_;

    Staff() {
        staffId_ = 0;
        nickname_ = "";
    }

    Staff(long int snid, std::string nname)
        : staffId_(snid), nickname_(nname){};

    static constexpr auto colTest1 =
        ColumnObject<Staff, long int>(&Staff::staffId_, "staff_id");
    static constexpr auto colTest2 =
        ColumnObject<Staff, std::string>(&Staff::nickname_, "nick_name");
};

int main() {
    constexpr auto colTest3 =
        ColumnObject<Staff, long int>(&Staff::staffId_, "staff_id");
}