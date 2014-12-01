#include <memory>
#include <stdio.h>
#include <string>

class base_type {
public:
    virtual ~base_type() {}
    
    virtual const std::string& name() const = 0;
}; /* class base_type */

typedef std::shared_ptr<base_type> base_type_ptr;

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

class type_with_info {
public:
    type_with_info(base_type_ptr info)
        : info_(std::move(info)) {}
    
    void print()
    {
        printf("Object with name: %s\n", info_->name().c_str());
    }

private:
    base_type_ptr info_;
}; /* class type_with_info */

int main(int argc, char* argv[])
{
    base_type_ptr info = std::make_shared<named_type>("object_name");
    type_with_info object(info);
    object.print();
    return 0;
}
