#include <vector>
#include <memory>
#include <time.h>

const size_t TOTAL = 1000;

struct shape
{
    virtual void draw() = 0;
    virtual ~shape() {}
};

struct box : public shape
{
    int w;  int h;
    virtual void draw() override
    {
    }
};

void f03()
{
    for (size_t k = 0; k < TOTAL; k++)
    {
        std::vector<shape*> shapes;
        for (size_t i = 0; i < TOTAL; i++)
        {
            shapes.emplace_back(new box());
        }

        for (size_t i = 0; i < TOTAL; i++)
        {
            delete shapes[i];
        }
    }
}

void f11()
{
    for (size_t k = 0; k < TOTAL; k++)
    {
        std::vector<std::unique_ptr<shape>> shapes;
        for (size_t i = 0; i < TOTAL; i++)
        {
            shapes.emplace_back(std::make_unique<box>());
        }
    }
}


void run_test(const char* message, void(*test)(void))
{
    time_t start = clock();
    test();
    printf("%s %d\n", message, static_cast<int>(clock() - start));

}

int main(int argc, char* argv[])
{
    printf("front\n\n");
    run_test("C++ 03 :", &f03);
    run_test("C++ 11:", &f11);

    run_test("C++ 03 :", &f03);
    run_test("C++ 11:", &f11);

    return 0;
}