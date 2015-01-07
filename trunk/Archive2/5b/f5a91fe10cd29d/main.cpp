#include <cstddef>
#include <string>
#include <iostream>

namespace bf {
    
 template <typename CharT = char, size_t N = 1024>
 struct Machine
 {
     CharT mem[N];
     size_t p;
     
     Machine()
      : mem{}, p{0}
     { }
     
     void run(const std::string &prog, std::istream &input, std::ostream &output)
     {
         for (size_t i = 0; i < prog.size(); ++i) {
             switch (c) {
                    case '+':
                        mem[p]++;
                        break;
                    case '-':
                        mem[p]--;
                        break;
                    case '>':
                        p++;
                        break;
                    case '<':
                        p--;
                        break;
                    case '.':
                        output << mem[p];
                        break;
                    case ',':
                        input.get(mem[p]);
                        break;
                    case '[':
                        break;
                    case ']':
                        break;
             }
         }
     }
 };
}

int main()
{
    bf::Machine<> m;
    m.run("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", std::cin, std::cout);
}
