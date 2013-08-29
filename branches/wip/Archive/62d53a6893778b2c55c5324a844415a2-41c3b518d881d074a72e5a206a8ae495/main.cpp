#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    std::string t_ques;
    char t_ans;
    int t_time_limit;

    std::getline(std::cin, t_ques);
    while (std::cin >> t_ans >> t_time_limit)
    {
        cout << t_ques << endl;
        cout << t_ans << endl;
        cout << t_time_limit << endl;

        std::cin.ignore();
        std::getline(std::cin, t_ques);
    }
}
