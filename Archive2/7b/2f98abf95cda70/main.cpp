#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

class object
{

public:

    unsigned int get_id() const
    {
        return _id;
    }

private:

    friend class tracking_factory;

    object(unsigned int id) : _id(id) { }

    unsigned int _id;

};

class tracking_factory
{

public:

    std::shared_ptr<object> get_object(unsigned int id, bool createIfNotFound = true)
    {
        auto i = _objects.find(id);
        if (i != end(_objects))
        {
            return i->second.lock();
        }
        else if (createIfNotFound)
        {
            return make_object(id);
        }
        else
        {
            return nullptr;
        }
    }

    unsigned int count_instances() const
    {
        return static_cast<unsigned int>(_objects.size());
    }

private:

    std::shared_ptr<object> make_object(unsigned int id)
    {
        std::shared_ptr<object> sp(
            new object(id),
            [this, id] (object* p)
        {
            _objects.erase(id);
            delete p;
        });

        _objects[id] = sp;

        return sp;
    }

    std::map<unsigned int, std::weak_ptr<object>> _objects;
};

void print_object_count(tracking_factory const& f)
{
    std::cout << "Number of objects: " << f.count_instances() << std::endl;
}
    
int main()
{
    tracking_factory f;

    print_object_count(f);

    auto p1 = f.get_object(42);

    print_object_count(f);

    {
        auto p2 = f.get_object(42);

        print_object_count(f);

        p1 = f.get_object(0);

        print_object_count(f);
    }

    print_object_count(f);

    p1.reset();

    print_object_count(f);
}
