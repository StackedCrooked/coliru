#include <cstddef>
#include <string>
#include <stack>
#include <iostream>

namespace bf {
    
 template <typename CharT = char, size_t N = 1024>
 struct Machine
 {

     
     void run(const std::string &prog, std::istream &input, std::ostream &output)
     {
        CharT mem[N] = {0};
        size_t p{0};
        std::stack<size_t> stack;
        
         for (size_t i = 0; i < prog.size(); ++i) {
             switch (prog[i]) {
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
                        output.put(mem[p]);
                        break;
                    case ',':
                        mem[p] = input.get();
                        break;
                    case '[':
                        if (mem[p]) {
                            stack.push(i);
                        } else {
                            while (i < prog.size() && prog[i] != ']') {
                                i++;
                            }
                            if (prog[i] == ']') {
                                i++;
                            }
                            else {
                                std::abort();
                            }
                        }
                        break;
                    case ']':
                        i = stack.top();
                        stack.pop();
                        break;
             }
         }
     }
 };
}

int main()
{
    bf::Machine<> m;
    m.run("+.", std::cin, std::cout);
    // m.run("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", std::cin, std::cout);
}
