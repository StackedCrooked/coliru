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
  
  std::cout << " --- push_back 5 Noisys ---\n";
  for (int i = 0; i != 5; ++i)
    noisys.push_back(Noisy{});
    
  std::vector<NoExceptNoisy> noexcept_noisys;
  
  std::cout << "\n --- push_back 5 NoExceptNoisy ---\n";  
  for (int i = 0; i != 5; ++i)
    noexcept_noisys.push_back(NoExceptNoisy{});
    
}
