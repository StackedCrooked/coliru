#include <memory>
#include <vector>

struct myType {};

class myClass {

public:
       std::vector<std::unique_ptr<myType> >& getMyMember();

private:
       std::vector<std::unique_ptr<myType> > m_myMember;
};

std::vector<std::unique_ptr<myType> >& myClass::getMyMember()
{
    return m_myMember;
}

int main()
{
    myClass x;
    auto& y = x.getMyMember();
    (void)y;
}