#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string.h>
#include <list>

int main()
{
    using namespace std;
     char chr1[256] = "It's " ;
     char chr2[256] = "rain Today.";
    strcat(chr1,chr2);
   // printf("%s\n",chr1);

    unsigned char abc;
    char test = 'a';
    abc= static_cast<unsigned char>(test);
    //printf("%c\n",abc);
    
    long station_area_code_ = 2;
    abc = static_cast<unsigned char>(station_area_code_);
    
    //printf("%d\n",area);
    std::ostringstream oss;
        
    oss << std::setw(3) << std::setfill('0') <<(int) abc << std::setw(2) << std::setfill('0') << (int) abc;
    
 //   std::cout << oss.str() << std::endl;
 
 
    /*
    char c[256]="";
    sprintf(c,"%d",abc);
    */

    /*
    char str1[30] = "ABC";
    char str2[] = "123";
    char *p = "abcd";

    strcat(str1, str2);     // 文字型配列に文字型配列を連結 
    printf("%s\n", str1);
    
    strcat(str1, p);        // 文字型配列にポインタの指す文字列リテラルを連結
    printf("%s\n", str1);
    
    strcat(str1, "xyz");    // 文字型配列に文字列リテラルを連結
    printf("%s\n", str1);
    */
        
    // short(2byte) →　char(1byte) にキャストすると桁あふれ
  /* 
    unsigned short tmps;
    tmps = 255;
    unsigned char tmpc;
    tmpc = static_cast <unsigned char>(tmps);
 
    printf("%d\n",tmpc);        
    
    return 0;
    */

    // ポインタの使い方
    //int *p;
    //int x = 5;
    //p = &x;
    //printf("%d\n",*p);

    // list の使い方

/*    list<int> i_list;
    list<int>::iterator begin;
    list<int>::iterator end;
    for(int i = 0; i <= 2; ++i){
        i_list.push_back(i);
    }
    
    begin = i_list.begin();
    
    printf("%d\n",*begin);
    ++begin;
    printf("%d\n",i_list.front());
    */
    
    list <vector<char>> clist;
    list <vector<char>>::iterator lbegin,lend;
    
    vector<char> cvect;
    vector<char>::iterator vbegin,vend;

    cvect.push_back('a');
    cvect.push_back('b');
    cvect.push_back('c');
    
    clist.push_back(cvect);


/*
    clist.push_back('a');
    clist.push_back('b');
    clist.push_back('c');
    
    char* cptr; // char型ポインタ
    char str[3] = "12"; // char型配列　最後の要素には自動でNULL入るので、文字数はn-1にしないとコンパイルエラー
    cptr = str;  // ポインタに配列の先頭アドレスが入る
    cptr = &str[0];  // このように直接先頭要素のアドレス指定しても同じこと
    
    printf("%s\n",cptr);
*/

// int型配列の先頭ポインタを渡して参照渡しにする
/*    int iarray[3];
    iarray[0] = 1;
    iarray[1] = 2;
    iarray[2] = 3;
    
    for (int j = 0; j < 3 ; j++ ) {
        printf("iarray[%d] = %d\n",j,iarray[j]);
    }

    int* iptr = NULL;
    iptr = iarray;
    
   for (int j = 0; j < 3 ; j++ ) {
        printf("iarray[%d] = %d\n",j,*iptr);
        ++iptr;
    }
*/

}
