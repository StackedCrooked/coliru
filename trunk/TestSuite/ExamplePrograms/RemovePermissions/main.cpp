#include <cstdlib>

int main()
{
    system("set -x; echo `pwd` ; find . | xargs -I {} chmod -R a-rwx {}");
}
