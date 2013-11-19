#include <iostream>

void greeting() {
  std::cout << "Dear Professor," << std::endl;
  std::cout << std::endl;
}
void print_signature() {
  std::cout << std::endl;
  std::cout << "Sincerely," << std::endl;
  std::cout << "Ian McGaunn" << std::endl;
}

void print_plea() {
  std::cout << "I was wondering if it would be at all possible "
            << "to get an extension of the due date for the first project.\n"
            << "I have been ardently working on the project, but I'm having"
            << " difficulty believing that I will be able to complete a\n"
            << "polished version by the due date on Thursday. Thank you for your consideration"
            << std::endl;
}

int main(int argc, char *argv[]) {
  greeting();
  print_plea();
  print_signature();
  return 0;
}