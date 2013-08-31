bool ordered(int args, double num, ...)
{
    bool order = true;
    double holder1, holder2;
    va_list arguments;
    va_start(arguments, num);
    holder1 = va_arg(arguments, double);
    for(int x = 2; x < args + 1; x++)
    {
        if(x % 2 == 0)
        {
            holder2 = va_arg(arguments, double);
            if(holder1 > holder2)
                order = false;
        }
        else if(x % 2 != 0)
        {
            holder1 = va_arg(arguments, double);
            if(holder2 > holder1)
                order = false;
        }
    }
    va_end(arguments);
    return order;
}

#include <cassert>
#undef NDEBUG

int main() {
    assert(ordered(2, 2, 1));
}
