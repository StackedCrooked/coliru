#include <iostream>
#include <atomic>
#include <memory>
#include <string>


int main() {
    // This SHOULD NOT compile. unique ptr is NOT trivially copied.
    std::atomic<std::unique_ptr<int>> a;
	
    a.store(std::unique_ptr<int>(new int{5}));
	for (size_t index = 0; index < 100; ++index){
	   a.load();	   
	}
    
	return 0;
}