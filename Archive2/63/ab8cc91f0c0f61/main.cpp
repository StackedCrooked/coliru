#include <iostream>
#include <vector>

struct Noisy {
  Noisy() { std::cout << "Noisy()\n"; }
  Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)\n"; }
  Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)\n"; }
  Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)\n"; return *this;}
  Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)\n"; return *this;}
};

struct NoExceptNoisy {
  NoExceptNoisy() { std::cout << "NoExceptNosy()\n"; }
  NoExceptNoisy(const NoExceptNoisy&) { std::cout << "NoExceptNoisy(const NoExceptNoisy&)\n"; }
  NoExceptNoisy(NoExceptNoisy&&) noexcept { std::cout << "NoExceptNoisy(NoExceptNoisy&&)\n"; }
  NoExceptNoisy& operator=(const NoExceptNoisy&) { std::cout << "operator=(const NoExceptNoisy&)\n"; return *this;}
  NoExceptNoisy& operator=(NoExceptNoisy&&) noexcept { std::cout << "operator=(NoExceptNoisy&&)\n"; return *this;}
};

int main() {
    
  std::vector<Noisy> noisys;
  
  std::cout << " --- emplace_back 5 Noisys ---\n";
  for (int i = 0; i != 5; ++i) {
    std::cout << i << "\n";
    noisys.emplace_back();
  }
    
  std::vector<NoExceptNoisy> noexcept_noisys;
  
  std::cout << "\n --- emplace_back 5 NoExceptNoisy ---\n";  
  for (int i = 0; i != 5; ++i) {
    std::cout << i << "\n";      
    noexcept_noisys.emplace_back();
  }
  
  std::vector<NoExceptNoisy> noisys3;
  std::cout << "\n --- reserve and emplace_back 5 NoExceptNoisy ---\n";  
  noisys3.reserve(5);
  for (int i = 0; i != 5; ++i) {
    std::cout << i << "\n";      
    noisys3.emplace_back();
  }    
  
  std::cout << "\n --- create vector of noisys of size 5 ---\n";
  std::vector<NoExceptNoisy> noisys4(5);   
}
