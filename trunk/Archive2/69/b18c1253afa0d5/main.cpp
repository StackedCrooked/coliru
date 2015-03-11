#include <iostream>
#include <csetjmp>
 
std::jmp_buf jump_buffer;
 
[[noreturn]] void a(int count) 
{
    std::cout << "a(" << count << ") called\n";
    std::longjmp(jump_buffer, count+1);  // setjump() will return count+1
}
 
int main()
{
    volatile int count = 0; // locals in scope where longjmp returns must be volatile
    if (setjmp(jump_buffer) != 9) { // equality against constant expression in an if
        a(count++);  // This will cause setjmp() to exit
    }
}