#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>

struct obj
{
    obj(std::string id)
        : id(id)
    {

    }

    obj(obj const&) = delete;
    obj& operator=(obj const&) = delete;
    obj& operator=(obj&&) = delete;
    obj(obj&&) = delete;


    void identif()
    {
        std::cout << "i am " << id << std::endl;
    }

    std::string id;
};

struct objs
{
    const std::unique_ptr< obj > obj_a;
    const std::unique_ptr< obj > obj_b;
    const std::unique_ptr< obj > obj_c;

    objs()
        : obj_a(std::unique_ptr< obj >( new obj("object a") ))
            ,obj_b(std::unique_ptr< obj >( new obj("object b") ))
            ,obj_c(std::unique_ptr< obj >( new obj("object c") ))
    {

    }

    void do_a()
    {
        std::cout << " member: " << obj_a->id << std::endl;
        std::cout << " method: ";
        obj_a->identif();
    }

    void do_b()
    {
        std::cout << " member: " << obj_b->id << std::endl;
        std::cout << " method: ";
        obj_b->identif();
    }

    void do_c()
    {
        std::cout << " member: " << obj_c->id << std::endl;
        std::cout << " method: ";
        obj_c->identif();
    }
};

int main(int argc, char** argv)
{

    objs obx;

    std::cout << " before move: " << std::endl;

    obx.do_a();
    obx.do_b();
    obx.do_c();

    std::cout << " after move: " << std::endl;

    std::unique_ptr< obj > newb(std::move(obx.obj_b));

    obx.do_a();
    obx.do_b();
    obx.do_c();

    return EXIT_SUCCESS;
}
