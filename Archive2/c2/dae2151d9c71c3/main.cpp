#include <iostream>
#include <random>
#include <array>
#include <string>

std::array<std::string, 3> questions {"Who are you?", "What is your purpose?", "What can you do?"};

std::string random_question() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, questions.size() - 1);
  
  return questions[dis(gen)];
}

int main() {
  for(int n = 0; n < 10; ++n) std::cout << random_question() << std::endl;
}
