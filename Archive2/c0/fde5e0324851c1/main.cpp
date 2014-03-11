#include <iostream>
#include <string>
 
class package
{
    public:
        package* next;
        package* child;
        static package* pack()
        {
            return new package();
        }
        template<typename... P>
        static package* pack(package* value, P... pkgs)
        {
            link(value,pkgs...);
            package* p = new package();
            p->child = value;
            return p;
        }
    private:
        static package* link()
        {
            return nullptr;
        }
        template<typename... P>
        static package* link(package* value, P... pkgs)
        {
            value->next = link(pkgs...);
            return value;
        }
};
 
int main()
{
    package* package1 = package::pack();
    package* package2 = package::pack();
    package* package3 = package::pack(package1,package2);
    std::cout << ((package3->child->next != nullptr) ? 1 : 0);
    std::cout << ((package3->child->next->next != nullptr) ? 1 : 0);
    std::cout << ((package3->child == package1) ? 1 : 0);
    std::cout << ((package3->child->next == package2) ? 1 : 0);
    return 0;
}