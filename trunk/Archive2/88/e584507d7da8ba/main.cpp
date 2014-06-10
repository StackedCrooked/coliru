#include <cstdio>
#include <thread>

#define FORCE(symbol) const volatile auto _use_ ## symbol = &symbol

struct X {
    X(const char* s) : s(s) {}
	~X() { printf("%s\n", s); fflush(stdout); }

	const char* s;
};

static const X preglobal         = "global #3";
static thread_local X global_tls = "global #2 (tls)";
static const X postglobal        = "global #1";

int main()
{
    // global_tls and local_tls get constructed (in that order) before the function local statics
    //FORCE(global_tls);

	static const X prelocal         = "local  #3";
	static thread_local X local_tls = "local  #2 (tls)";
	static const X postlocal        = "local  #1";

    // local_tls and global_tls get constructed (in that order) between the function local statics
    FORCE(global_tls);
    
	std::thread([] {
        // control order of global_tls/inner_tls destruction, local_tls never constructed for some reason
        FORCE(global_tls);
        FORCE(local_tls);
        
        static thread_local X inner_tls = "inner  #1 (tls)";
        
	}).join();
    
    printf("exiting main\n");
}
