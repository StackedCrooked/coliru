#include <iostream>
#include <list>

int returner(int x);

int main ()
{
 std::cout << returner(1) << std::endl;
 return 0;
}

int returner(int x)
{
    switch(x)
    {
        switch (x)
        case 1:
        case 2:
        case 3:
        case 4:
            return 1; 
        default: 
            return 2;   
    }
}

