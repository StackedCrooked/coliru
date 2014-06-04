#include <iostream>
using namespace std;
int main()
{
    char yen;
    string emp;
    float week1 = 0.0, week2 = 0.0, sum=0.0, sum2=0.0;
    int week, oth;

    cout << " Employee no                   : ";
    cin >> emp;
    cout << " Week no                       : ";
    cin >> week;
    cout << " OT hours                      : ";
    cin >> oth;
    cout << " Do you want to continue? Y/N  : ";
    cin >> yen;

    if (yen == 'y' || yen == 'Y')
    {
        cout << " Employee no                   : ";
        cin >> emp;
        cout << " Week no                       : ";
        cin >> week;
        cout << " OT hours                      : ";
        cin >> oth;

        if (week == 1)
        {
//        {
            if (emp == "Emp10" || emp == "emp10")
            {
                sum = (oth * 300.0);
                week1 = week1 + sum;
            }
            else if (emp == "Emp12" || emp == "emp12")
            {
                sum = (oth * 200.0);
                week1 = week1 + sum;
            }
            else if (emp == "Emp105" || emp == "emp105")
            {
                sum = (oth * 200.0);
                week1 = week1 + sum;
            }
            else if (emp == "Emp08" || emp == "emp08")
            {
                sum = (oth * 100.0);
                week1 = week1 + sum;
            }
            else if (emp == "Emp11" || emp == "emp11")
            {
                sum = (oth * 100.0);
                week1 = week1 + sum;
            }
            else {
                std::cerr << "error\n";
                return 1;
            }
        }
//    }
//}
        else if (week == 2)
        {
            if (emp == "Emp10" || emp == "emp10")
            {
                sum2 = (oth * 300.0);
                week2 = week2 + sum2;
            }
            else if (emp == "Emp12" || emp == "emp12")
            {
                sum2 = (oth * 200.0);
                week2 = week2+ sum2;
            }
            else if (emp == "Emp105" || emp == "emp105")
            {
                sum2 = (oth * 200.0);
                week2 = week2 + sum2;
            }
            else if (emp == "Emp08" || emp == "emp08")
            {
                sum2 = (oth * 100.0);
                week2 = week2 + sum2;
            }
            else if(emp == "Emp11" || emp == "emp11")
            {
                sum2 = (oth * 100.0);
                week2 = week2 + sum2;
            }
            else {
                std::cerr << "error\n";
                return 1;
            }
        }
    }
//}
    else (yen == 'n' || yen == 'N');
    {
        cout << " Total OT cost for week 1 : ";
        cout << week1 << ".00" << endl;
        cout << " Total OT cost for week 2 : ";
        cout << week2 << ".00" << endl;
    }
    return 0;
}