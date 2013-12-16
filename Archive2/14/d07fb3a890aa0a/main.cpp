#include <iostream>

int main()
{
    const int size = 2000;
    std::cout << "#include <iostream>\n\n";
    std::cout << "int main()\n{\n";
    std::cout << "    int i0 = " << size << ";";
    for (int i = 1; i < size; ++i)
    {
        std::cout << "    int ";
        for (int j = 0; j < i; ++j) std::cout << "*";
        std::cout << " i" << i << " = &i" << i-1 << ";\n";
    }
    std::cout << "    std::cout << ";
    for (int i = 1; i < size; ++i) std::cout << "*";
    std::cout << "i" << size-1 << " << \"\\n\";\n";
    std::cout << "    return 0;\n}\n";
    return 0;
}