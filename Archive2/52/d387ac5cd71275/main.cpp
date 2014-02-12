  #include <iostream>
  #include <string>
  #include <vector>
  
  struct Person {
      std::string a;
      Person (std::string s) : a(s) {}
  };

int alloc_count = 0;
int allocated_size = 0;

void *operator new(std::size_t s) { ++alloc_count; allocated_size += s; return std::malloc(s); }
void operator delete(void *ptr) { std::free(ptr); } 

int main()
{
    std::vector<Person> p;
    std::string s;
      
    while (std::cin >> s) {
      p.emplace_back(std::move(s));
    }
    std::cout << alloc_count << ' ' << allocated_size << '\n';
}