#include <cstdlib>
#include <ctime>
#include <array>

struct T
{
    void setFlag(bool x) { this->x = x; }
private:
    bool x;
};

int main()
{
    std::srand(std::time(0));
    const unsigned int N = 1000000;
    
    T obj;
    std::array<int, N> A;
    
    for (unsigned int i = 0; i < N; i++)
        A[i] = std::rand();
    
    #ifdef LOOP_A
        for (unsigned int i = 0; i < N; i++)
        {
            if(A[i] > 10)
                obj.setFlag(true);
            else
                obj.setFlag(false);
        }
    #endif
    
    #ifdef LOOP_B
        for (unsigned int i = 0; i < N; i++)
        {
            obj.setFlag(A[i] > 10);
        } 
    #endif
}