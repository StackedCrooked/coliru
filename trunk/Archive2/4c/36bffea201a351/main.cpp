#includ e<iostream>

int main()
{
    int sum = 0, value = 0;
    while (std::cin >> value)
        sum += value;
    std::cout << "Sum is: " << sum << std::endl; // this doesn't do anything
    std::cin.ignore().get();
    return 0;
}