#include <functional>

class animal {
protected:
    animal() {}
    void eat(int x) {}
};


class human
    : private animal
{
public:
    typedef animal base_type;
    using base_type::eat;
    
    animal* self() { return this; }
};

class stomach {
public:
    stomach(std::function<void(int)> feed) {}
};

class lady
    : public human
{
public:
    typedef lady        this_type;
    typedef human       base_type;

    lady()
        : base_type()
        , m_Stomach(std::bind(&base_type::eat, self(), std::placeholders::_1))
    {
    }

private:
    stomach m_Stomach;
};

int main()
{
    lady gaga;
    gaga.eat(42);
}
