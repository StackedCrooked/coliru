#include <cstdio>

void print_to_console() {
    std::printf( "Hello from print_to_console()\n" );
}

void foo(){
  std::printf("hello world\n");
  print_to_console(); // this could be printed from anything
}

int main()
{
    char buffer[1024];
    auto fp = fmemopen(buffer, 1024, "w");
    if ( !fp ) std::printf("error");
    
    auto old = stdout;
    stdout = fp;
    
    foo(); //all the std::printf goes to buffer (using fp);
    
    std::fclose(fp);
    stdout = old; //reset
    
    std::printf("<redirected-output>\n%s</redirected-output>", buffer);
}