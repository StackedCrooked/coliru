#include <stdio.h>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

template <typename I, typename F> void perm_ins(I pb, I pe, F visit)
{
    if (pb == pe || pb == pe-1)
    {
        visit();
        return;
    }

    perm_ins(pb + 1, pe, [pb, pe, visit]()
    {
        visit();

        for (I pc = pb; pc != pe-1; ++pc)
        {
            swap(*pc, *(pc+1));
            visit();
        }

        rotate(pb, pe-1, pe);
    });
}

void perm_adj(char *pb, char *pe, function<void (const char *, const char *)> visit)
{
    if (pb == pe || pb == pe-1)
    {
        visit(pb, pe);
        return;
    }

    bool fwd = true;

    perm_adj(pb + 1, pe, [&](const char *, const char *)
    {
        if (!fwd) rotate(pb, pb+1, pe);

        visit(pb, pe);

        if (fwd)
        {
            for (char *pc = pb; pc != pe-1; ++pc)
            {
                swap(*pc, *(pc+1));
                visit(pb, pe);
            }
        }
        else
        {
            for (char *pc = pe-1; pc != pb; --pc)
            {
                swap(*pc, *(pc-1));
                visit(pb, pe);
            }
        }

        if (fwd) rotate(pb, pe-1, pe);
        fwd = !fwd;
    });
}

int main()
{
    char pp[] = "1234";

    int i = 0;
    perm_ins(pp, pp+4, [i, &pp]() mutable { printf("%02d: %s\n", ++i, pp); });

    puts("");

    perm_adj(pp, pp+4, [i](const char *pb, const char *) mutable { printf("%02d: %s\n", ++i, pb); });
}
