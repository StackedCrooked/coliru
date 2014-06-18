#include <cstdio>
class b;
class a {
public:
        void stuff(int b) {
                std::printf("stuff(int) a\n");
        }
        void stuff(int *b) {
                std::printf("stuff(*int) a\n");
        }
};
class b : public a {
public:
        void stuff(int b) {
                std::printf("stuff(int) b\n");
        }
};
 
int main()
{
        b someb;
        ((a)someb).stuff(nullptr);
        return 0;
}