#include <iostream>
#include <string>

#include "lundi.hpp"


//I use object.get(name) and object.set(name, value) on the assumption
//implementation is easier.  But if possible, object["name"] = value would be better.

void exceptionErrorReporter(std::string const& s) {
    throw lua::exception(s);
}

class person {
    int age;
public:
    person(std::string name_, int age_) :name(name_), age(age_) {}
    std::string name;
    int print_age() const {std::cout << age;}
};

//lua types only loosly mirror cpp types
lua::variant assign_to_lua(lua::state& lua, const person& src, lua::variant& dst) {
    dst.assign_new_table(); //I'm not sure I like this at all
    dst.set("name", name);
    dst.set("age", age);
    dst.set("print_age", person::get_age);
    return dst;
}

person create_from_lua(lua::state& lua, lua::variant& src) {
    return person(src.get("name"),src.get("age"));
}

//potentially comes with a default based on create_from_lua
bool assign_from_lua(lua::state& lua, lua::variant& src, const person& dst) {
    dst = person(src.get("name"),src.get("age"));
    return true;
}





void f_cpp(const person& p) {std::cout << p.print_age() << '\n';}

int main() {
    lua::state lua(&exceptionErrorReporter);
    
    // cpp -> lua conversion
    person p1("STEVE", 20);    
    lua::variant p2 = assign_to_lua(lua, p1, lua.global().get("v"));
    lua.eval("print(v.name, \" \", v.age)");
    lua.eval("v.print_age()");
    
    // lua -> cpp conversion
    person p2 = create_from_lua(lua, lua.global().get("v"));
    std::cout << p2.name << " " << p2.get_age() << '\n';
    p2 = assign_from_lua(lua, lua.global().get("v"));
    std::cout << p2.name << " " << p2.get_age() << '\n';
    
    // pass C++ object to lua function
    lua.eval("f = function(p) p.print_age() end");
    lua.global().call("f")(p1);
    
    //pass lua object to C++ function
    lua.global().set("f", f_cpp);
    lua.global().call("f")(lua.global().get("v")); 
}

