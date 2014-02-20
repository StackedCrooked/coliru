#include <iostream>
#include <string>

int main()
{
    std::string s = R"(
1
Second Line of Data for this entry
Here is the content

2
Second Line of Data for this entry
Here is the content that can be multiline
It is multiline for entry two

3 
Second Line of Data for this entry
More content
)";

    std::cout << s;
}
