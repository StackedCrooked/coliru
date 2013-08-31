#include <stdexcept>
#include <iostream>

#include <memory>

/* old_library.c */
char *allocate_lots()
{
    return static_cast<char*>(malloc(1024));
}

struct my_exception : virtual std::exception {
    const char* const msg;
    my_exception(const char* const msg) : msg(msg) {}
    const char* what() const noexcept { return msg; }
};

struct my_class
{
    struct Free { void operator() (char* p) const { free(p); } };

    void my_func()
    {
        std::unique_ptr<char, Free> mem;

        mem.reset(allocate_lots());
        bool problem = use(mem.get());

        if(problem)
        {
            throw my_exception("Oh noes! This will be caught higher up");
        }
    }

    static bool use(char*) { return true; }
};

int main()
{
    my_class prog;
    prog.my_func();
}
