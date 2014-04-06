#include <iostream>
#include <string>

struct member
{
    member( const std::string& value, const std::string& name, const std::string& held_by )
        : value(value), member_name(name), containing_object_name(held_by) {}

    std::string value ;

    const std::string member_name ;
    const std::string containing_object_name ;

    member& operator= ( const member& that )
    {
        static int n = 0 ;
        std::cout << ++n << ". "
                  << this->containing_object_name << '.' << this->member_name << " = "
                  << that.containing_object_name << '.' << that.member_name << '\n' ;

        value = that.value ;
        return *this ;
    }
};

struct holder
{
    holder( const char* holder_name, const char* a, const char* b, const char* c )
       : one( a, "one", holder_name ),
         two( b, "two", holder_name ),
         three( c, "three", holder_name ) {}

    member one ;
    member two ;
    member three ;

    // *** the class does not have a user-defined assignment operator ***
    // *** the semantics of implicitly defined assignment is member-wise assignment
    // *** ie. assign members one by one in the order of declaration
};

int main()
{
    holder lhs( "lhs", "a", "b", "c" ) ;
    const holder rhs( "rhs", "dd", "eee", "ffff" ) ;

    std::cout << "value of members before assignment: " << lhs.one.value << ',' << lhs.two.value << ','
              << lhs.three.value << "\n\n" ; // value of members before assignment: a,b,c

    // assign rhs to lhs using the implicitly defined assignment operator
    lhs = rhs ; // this performs member-wise assignment
                // ie. assign members of rhs to the corresponding members in lhs
                // in the order of declaration of the members
                // 1. lhs.one = rhs.one
                // 2. lhs.two = rhs.two
                // 3. lhs.three = rhs.three

    std::cout << "\nvalue of members after assignment: " << lhs.one.value << ',' << lhs.two.value << ','
               << lhs.three.value << '\n' ; // value of members after assignment: dd,eee,ffff
}
