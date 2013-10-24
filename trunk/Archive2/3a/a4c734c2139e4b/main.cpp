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
    int count = setjmp(jump_buffer);
    if (count != 9) {
        a(count);  // This will cause setjmp() to exit
    }
}