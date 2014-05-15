#include <map>
#include <memory>
#include <algorithm>
#include <iostream>

class object
{
public:
    int get_id() const { return _id; }
private:
    friend class tracking_factory;
    object(int id) : _id{id} { }
    int _id;
};

class tracking_factory
{
public:
    using id_type = int;
    using o_ptr = std::shared_ptr<object>;
public:
    o_ptr get_or_make_object(id_type id);
    int count_instances() const;
private:
    using w_ptr = std::weak_ptr<object>;
    using object_map = std::map<id_type, w_ptr>;
private:
    o_ptr make_tracked_object(id_type id);
    o_ptr fabricate_object(id_type id);
    void register_object(o_ptr o);
private:
    object_map _objects;
};

tracking_factory::o_ptr tracking_factory::get_or_make_object(id_type id)
{
    auto i = _objects.find(id);
    if (i != end(_objects))
    {
        return i->second.lock();
    }
    else
    {
        return make_tracked_object(id);
    }
}

tracking_factory::id_type tracking_factory::count_instances() const
{
    return static_cast<id_type>(_objects.size());
}

tracking_factory::o_ptr tracking_factory::make_tracked_object(id_type id)
{
    auto p = fabricate_object(id);
    _objects[id] = p;
    return p;
}

tracking_factory::o_ptr tracking_factory::fabricate_object(id_type id)
{
    return o_ptr{new object{id},
                 [this, id] (object* p)
                 {
                     _objects.erase(id);
                     delete p;
                 }};
}

void tracking_factory::register_object(o_ptr o)
{
    auto id = o->get_id();
    _objects[id] = o;
}

void print_object_count(tracking_factory const& f)
{
    std::cout << "Number of objects: " << f.count_instances() << std::endl;
}
    
int main()
{
    tracking_factory f;

    print_object_count(f);

    auto p1 = f.get_or_make_object(42);

    print_object_count(f);

    {
        auto p2 = f.get_or_make_object(42);

        print_object_count(f);

        p1 = f.get_or_make_object(0);

        print_object_count(f);
    }

    print_object_count(f);

    p1.reset();

    print_object_count(f);
}
