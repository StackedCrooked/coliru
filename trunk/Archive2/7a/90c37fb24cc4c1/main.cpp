#include <iostream>
#include <string>

class object {
public:
    object(bool a)
    {
        if (a)
            std::cout << "Oh, hi!\n";
    }

private:
    object(const object& b);
    object& operator=(const object&);
}; /* class object */


int main()
{
    //object o;
    object o=true;
    return 0;
}
