#include<iostream>
#include<cmath>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int main()
{
    char html[] ="<tr> \
        <td>row 1, cell 1 < / td > \
        <td>row 1, cell 2 < / td > \
        < / tr> \
        <tr> \
        <td>row 2, cell 1 < / td > \
        <td>row 2, cell 2 < / td > \
        < / tr> ";

    for (int i = 0; i < sizeof(html)/sizeof(html[0]); i++)
    {
        if (html[i] == '<')
        {
            for (int j = i + 1;; j++)
            {
                if (html[j] == '>')
                {
                    for (int c = j + 1;; c++)
                    {
                        if (html[c] == '<')
                            break;
                            
                        std::cout << html[c];
                    }
                    
                    break;
                }
            }
        }
    }
    return 0;
}