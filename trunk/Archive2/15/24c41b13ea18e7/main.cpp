#include <iostream>

class outer {
public:
    struct inner {
        inner()
            : dummy(0) {}

        int dummy;
    }; /* struct inner */

    outer(const inner& inner)
        : inner_(inner)
    {
    }

private:
    const inner& inner_;
}; /* class outer */

int main()
{
    //outer o(inner());
    outer o(outer::inner());

    return 0;
}
