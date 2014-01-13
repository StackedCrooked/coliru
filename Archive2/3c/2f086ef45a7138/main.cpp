#include <stdio.h>
#include <boost/utility.h>

class Test : private boost::noncopyalbe {
    public int A;
};
int main() {
    Test t = new Test()
    t.A = 100;
    Test tc = t;
    printf("%d\n",t.A);
}