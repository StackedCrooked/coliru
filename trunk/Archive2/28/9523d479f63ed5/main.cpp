//http://stackoverflow.com/questions/27770050/not-able-to-understand-ostream
//*************STACK CODE***************//

//VERY GOOD EXAMPLE TO UNDERSTAND RULE OF THREE FOR BEGINEERS http://www.drdobbs.com/c-made-easier-the-rule-of-three/184401400
//RULE OF THREE : Video : https://www.youtube.com/watch?v=F-7Rpt2D-zo
//Thumb Rule : Whenever we have class which has members pointing to heap space we should implement Rule of three.
//Concepts : Shallow Copy and Deep Copy

#include <iostream>
#include <stdexcept>
template <class T>
class Mystack
{
private:
    T *input;
    int top;
    int capacity;
public:
    Mystack();
    ~Mystack();
    void push(T const& x);
    void pop();
    T& topElement() const;
    bool isEmpty() const;
    void print();
};
template <class T>
Mystack<T>::Mystack()
{
    top = -1;
    capacity = 5;
    input = new T[capacity];
}
template <class T>
Mystack<T>::~Mystack() //Since we are using destructor explictly we need to apply Rule of 3
{
    delete [] input;
}
template <class T>
void Mystack<T>::push(T const& x)  //Passing x by Const Reference // Valus of x cannot be changed now in the function!
{
    if (top + 1 == capacity)
    {
        T *vec = new T[capacity * 2];
        for (int i = 0; i <= top; i++)
        {
            vec[i] = input[i];
        }
        delete []input; // Avoiding Memory Leak.
        input = vec;
        capacity *= capacity;
    }
    top++;
    std::cout << x;
    std::cout << &x;
    input[top] = x;
}
template <class T>
void Mystack<T>::pop()
{
    if (isEmpty())
    {
        throw std::out_of_range("Stack Underflow");
    }
    else
    {
        std::cout << "The popped element is" << input[top--];

    }
}
template <class T>
bool Mystack<T>::isEmpty() const
{
    if (top == -1)
    {
        std::cout << "Is Empty" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Not Empty" << std::endl;
        return false;
    }
}
template <class T>
T& Mystack<T>::topElement() const
{
    if (top == -1)
    {
        throw std::out_of_range("No Element to Display");
    }
    else
    {
        std::cout << "The top element is : " << input[top];
        return input[top];
    }
}
template <class T>
void Mystack<T>::print()
{
    for (int i = 0; i <= top; i++)
    {
        std::cout << input[i] << " ";
    }
}
int main()
{
    Mystack<int> s1;
    Mystack<float> s2;
    Mystack<char> s3;
    int choice;
    int int_elem;
    float float_elem;
    char char_elem;
    std::cout << "Enter the type of stack" << std::endl;
    std::cout << "1. int ";
    std::cout << "2. float ";
    std::cout << "3. Char"<< std::endl;
    std::cin >> choice;
    if (choice == 1)
    {
        int  ch = 1;
        while (ch > 0)
        {
            std::cout << "\n1. Push ";
            std::cout << "2. Top ";
            std::cout << "3. IsEmpty ";
            std::cout << "4. Pop ";
            std::cout << "5. Exit ";
            std::cout << "6. Print"<<std::endl;
            std::cout << "Enter the choice" << std::endl;
            std::cin >> ch;
            switch (ch)
            {
            case 1:
                std::cout << "Enter the number to be pushed" << std::endl;
                std::cin >> int_elem;
                s1.push(int_elem);
                break;
            case 2:
                std::cout << "Get the TOP Element" << std::endl;
                try
                {
                    s1.topElement();
                }
                catch (std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error:" << oor.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Check Empty" << std::endl;
                s1.isEmpty();
                break;
            case 4:
                std::cout << "POP the element" << std::endl;
                try
                {
                    s1.pop();
                }
                catch (const std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error: " << oor.what() << '\n';
                }
                break;
            case 5:
                exit(0);
            case 6:
                s1.print();
                break;
            default:
                std::cout << "Enter a valid input";
                break;
            }
        }
    }
    else if (choice == 2)
    {
        int  ch = 1;
        while (ch > 0)
        {
            std::cout << "\n1. PUSH" << std::endl;
            std::cout << "2. TOP" << std::endl;
            std::cout << "3. IsEmpty" << std::endl;
            std::cout << "4. POP" << std::endl;
            std::cout << "5. EXIT" << std::endl;
            std::cout << "6. Print" << std::endl;
            std::cout << "Enter the choice" << std::endl;
            std::cin >> ch;
            switch (ch)
            {
            case 1:
                std::cout << "Enter the number to be pushed" << std::endl;
                std::cin >> float_elem;
                s2.push(float_elem);
                break;
            case 2:
                std::cout << "Get the TOP Element" << std::endl;
                try
                {
                    s2.topElement();
                }
                catch (std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error:" << oor.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Check Empty" << std::endl;
                s2.isEmpty();
                break;
            case 4:
                std::cout << "POP the element" << std::endl;
                try
                {
                    s2.pop();
                }
                catch (const std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error: " << oor.what() << '\n';
                }
                break;
            case 5:
                exit(0);
            case 6:
                s2.print();
                break;
            default:
                std::cout << "Enter a valid input";
                break;
            }
        }
    }
    else if (choice == 3)
    {
        int  ch = 1;
        while (ch > 0)
        {
            std::cout << "\n1. PUSH" << std::endl;
            std::cout << "2. TOP" << std::endl;
            std::cout << "3. IsEmpty" << std::endl;
            std::cout << "4. POP" << std::endl;
            std::cout << "5. EXIT" << std::endl;
            std::cout << "6. Print" << std::endl;
            std::cout << "Enter the choice" << std::endl;
            std::cin >> ch;
            switch (ch)
            {
            case 1:
                std::cout << "Enter the number to be pushed" << std::endl;
                std::cin >> char_elem;
                s3.push(char_elem);
                break;
            case 2:
                std::cout << "Get the TOP Element" << std::endl;
                try
                {
                    s3.topElement();
                }
                catch (std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error:" << oor.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Check Empty" << std::endl;
                s3.isEmpty();
                break;
            case 4:
                std::cout << "POP the element" << std::endl;
                try
                {
                    s3.pop();
                }
                catch (const std::out_of_range &oor)
                {
                    std::cerr << "Out of Range error: " << oor.what() << '\n';
                }
                break;
            case 5:
                exit(0);
            case 6:
                s3.print();
                break;
            default:
                std::cout << "Enter a valid input";
                break;
            }
        }
    }
    else
        std::cout << "Invalid Choice";
    std::cin.get();
}