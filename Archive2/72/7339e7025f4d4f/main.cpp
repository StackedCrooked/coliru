#include <memory>
#include <iostream>

using namespace std;

struct concept
{
    virtual void perform() = 0;
};


struct model : concept, enable_shared_from_this<model>
{
    void perform() override {
        cout << "my pointer is " << shared_from_this().get() << endl;
    }
};

int main(int, const char *[])
{
//    shared_ptr<concept> concept_ptr = make_shared<model>();
    shared_ptr<concept> concept_ptr { new model };
    concept_ptr->perform();
    return 0;
}
