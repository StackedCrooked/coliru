#include <stdio.h>
#include <string>

class base_type {
public:
    virtual ~base_type() {}
    
    virtual const std::string& name() const = 0;
}; /* class base_type */

class named_type : public base_type {
public:
    named_type(std::string name)
        : name_(std::move(name)) {}

    const std::string& name() const
    {
        return name_;
    }

private:
    named_type(const named_type&);
    named_type& operator=(const named_type&);

    std::string name_;
}; /* class named_type */

class named_object_factory {
public:
    base_type create(std::string name)
    {
        named_type object(std::move(name));
        return std::move(object);
    }
}; /* class named_object_factory */

int main(int argc, char* argv[])
{
    named_type object("object_name");
    printf("Name: %s\n", object.name().c_str());
    return 0;
}
