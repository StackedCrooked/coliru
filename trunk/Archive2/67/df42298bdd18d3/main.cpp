#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main(){

    int c = 0, n = 0, str_n = 0, t_cost = 0;

    int str[1000];

    cin >> c; //test case

    while (c > 0){

        cin >> n; //문자열 수

 

      for(int i=0; i< n; i++) {

          cin >> str_n; //문자열 길이

            str[i] = str_n;  //문자열 길이 배열에 저장

       }

      //문자열 더함

      for(int i=0; i < n; i++){

           sort(str+i, str+n);

           if( i == (n-1) ) break;

          else {

              str[i+1] = str[i]+str[i+1];

              t_cost += str[i+1];

          }

      }

      //총 비용 출력

      cout << t_cost << endl;


       c--;

   }



    return 0;

}
