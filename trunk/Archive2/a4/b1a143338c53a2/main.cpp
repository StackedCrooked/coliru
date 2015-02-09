#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

struct book_base
{
    std::string name;
    std::string author;
    std::string ISBN;
};

class book_instance;

class book_record : public std::enable_shared_from_this<book_record>
{
    const book_base book;
    std::vector<book_instance*> instances;
  public:
    book_record(const book_base& b) : book(b) {}
    std::shared_ptr<book_record> get_pointer()
    {
        return shared_from_this();
    }
    const std::vector<book_instance*>& instance_table() const
    {
        return instances;
    }
    bool register_instance(book_instance* inst)
    {
        if(std::find(instances.begin(), instances.end(), inst) != instances.end())
            return false;
        instances.push_back(inst);
        return true;
    }
    bool unregister_instance(book_instance* inst)
    {
        auto it = std::find(instances.begin(), instances.end(), inst);
        if(it == instances.end())
            return false;
        instances.erase(it);
        return true;
    }
};

class book_instance
{
    std::shared_ptr<book_record> ptr;
  public:
    std::string temp;
    book_instance(book_record& r, std::string name): ptr(r.get_pointer()), temp(name)
    {
        ptr->register_instance(this);
    }
    ~book_instance()
    {
        ptr->unregister_instance(this);
    }
    const book_record& base()
    {
        return *ptr;
    }

};


int main()
{
    std::vector<std::shared_ptr<book_record>> books = {{
        std::make_shared<book_record>(book_base{"a", "b", "c"}),
        std::make_shared<book_record>(book_base{"d", "e", "f"})
    }};
    book_instance foo(*books[1], "foo");
    book_instance bar(*books[1], "bar");
    for(auto p: bar.base().instance_table())
        std::cout << p->temp << '\n';
}
