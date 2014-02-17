#include <iostream>  

02 #include <fstream>  

03 #include <iomanip>  

04 #include <string>  

05 using namespace std;  

06 void main (void)  

07 {  

08 /*****Declare Variables*****/ 

09     ifstream fin;  

10     ofstream fout;  

11     int hours, counter, num;  

12     float pay_rate, tax;  

13     double avg_sal, total_sal;  

14     string dataf_name, name, dataf_out;  

15    

16     /**********Input***********/  

17 cout<< "Enter input file name:";  

18 getline(cin,dataf_name);  

19 cout<< "Enter output file name:";  

20 getline(cin,dataf_out);  

21 //cin>>dataf_out;  

22 fin.open (dataf_name.c_str());  

23 if (fin.fail())  

24 cout<< "Bad file name!";  

25 else 

26 {  

27     fout.open("out.txt");  

28     cout<<setprecision(2);  

29     fout<<setprecision(2);  

30     cout<<\t"This pogram will calculate and report user's tax liabilities."<<endl;  

31     cout<<\t"===================================================="<<endl;  

32     cout<<\t"Name"<<endl<<name;  

33     cout<<setw(10)<<"Hours"<<endl<<hours;  

34     cout<<setw(20)<<"Pay Rate"<<endl<<pay_rate;  

35     cout<<setw(30)<<"Salary"<<endl<<salary;  

36     cout<<setw(40)<<"Tax"<<tax<<endl;  

37     cout<<\t"===================================================="<<endl;  

38     getline(fp, name);  

39     while (fp) // while (!fp.eof))  

40     {  

41         fin>>hours;  

42         fin>>pay_rate;  

43         if hours < 0   

44             cout<<"Invalid hours";  

45         if pay_rate < 0  

46             cout<<"Invlaid pay rate";  

47         else 

48         salary = pay_rate * hours;  

49         if salary < 3500  

50         tax = 0;  

51 else if salary < 8000  

52     tax = [((salary - 3500)*.06)+ 105];  

53 else if salary < 20000  

54     tax = [((salary - 8000)*.11)+ 375];  

55 else if salary < 34000  

56     tax = [((salary - 20000)*.17+ 1695];  

57 else if salary < 52000  

58     tax = [((salary - 34000)*.24+ 4075];  

59 else if salary > 52000  

60     tax = [((salary - 52000)*.32+ 8395];  

61 infile>>name;  

62 while(infile)  

63 {  

64 counter = 0;  

65 sum = 0;  

66 infile>>num;  

67 while (infile)  

68 {  

69     total_sal = total_sal + num;  

70     salary++;  

71     infile>> num;  

72 }  

73 avg_sal= total_sal/num;  

