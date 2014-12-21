#include <iostream>
using namespace std;

#include <fstream>
#include <sstream>
#include <unistd.h>
// read bottom of stack from /proc/<pid>/stat
unsigned long bottom_of_stack() {
    unsigned long bottom = 0;
	ostringstream path;
	path << "/proc/" << getpid() << "/stat";
	ifstream stat(path.str());
	// possibly not the best way to parse /proc/pid/stat
	string ignore;
	if(stat.is_open()) {
		// startstack is the 28th field
		for(int i = 1; i < 28; i++)
			getline(stat, ignore, ' ');
		stat >> bottom;
	}
	return bottom;
}

#include <sys/resource.h>
rlim_t get_max_stack_size() {
	rlimit limits;
	getrlimit(RLIMIT_STACK, &limits);
	return limits.rlim_cur;
}

#define UNW_LOCAL_ONLY
#include <libunwind.h>

// using global variables for conciseness
unw_cursor_t frame_cursor;
unw_context_t unwind_context;

// approximate bottom of stack using SP register and unwinding
unw_word_t appr_bottom_of_stack() {
	unw_word_t bottom;
	unw_getcontext(&unwind_context);
	unw_init_local(&frame_cursor, &unwind_context);
	do {
		unw_get_reg(&frame_cursor, UNW_REG_SP, &bottom);
	} while(unw_step(&frame_cursor) > 0);
	return bottom;
}

// must not inline since that would change behaviour
unw_word_t __attribute__((noinline)) current_sp() {
	unw_word_t sp;
	unw_getcontext(&unwind_context);
	unw_init_local(&frame_cursor, &unwind_context);
	unw_step(&frame_cursor); // step to frame before this function
	unw_get_reg(&frame_cursor, UNW_REG_SP, &sp);
	return sp;
}

// a little helper for absolute delta of unsigned integers
#include <algorithm>
template<class UI>
UI abs_udelta(UI left, UI right) {
	return max(left,right) - min(left,right);
}

unsigned long global_bottom;
rlim_t global_max;

// a test function to grow the call stack
int recurse(int index) {
	if(index < 2 ) {
		auto stack_size = abs_udelta(current_sp(), global_bottom);
		cout << "Current stack size: " << stack_size << "\tStack left: " << global_max - stack_size << '\n';
		return index;
	}
	return recurse(index - 1) + recurse(index - 2); // do the fibonacci
}

int main() {
	global_max = get_max_stack_size();
	global_bottom = bottom_of_stack();
	unw_word_t global_appr_bottom = appr_bottom_of_stack();
	cout << "Maximum stack size: " << global_max << '\n';
	cout << "Approximate bottom of the stack by unwinding: " << (void*)global_appr_bottom << '\n';
	if(global_bottom > 0) {
		cout << "Bottom of the stack in /proc/<pid>/stat: " << (void*)global_bottom << '\n';
		cout << "Approximation error: " << abs_udelta(global_bottom, global_appr_bottom) << '\n';
	} else {
		global_bottom = global_appr_bottom;
		cout << "Could not parse /proc/<pid>/stat" << '\n';
	}
	cout << "Result of recursion: " << recurse(6); // use the result so call won't get optimized out
}
