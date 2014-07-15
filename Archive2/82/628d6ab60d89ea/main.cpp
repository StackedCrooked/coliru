#include "stdafx.h"
#include <iostream>

using namespace std;

char *strReverse(char * sourcestr)
{
    int j = 0, i = 0,begin,end;
	char *str = sourcestr;
	char temp;
	j = strlen(str) - 1;
	cout << " string = " << str << endl;
	//先将字符串进行全部倒转 变成 .nijnaiT morf emoc I
	while (j > i)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		j --;
		i ++;
	}
	cout << " string = " << str << endl;

	//然后进行按单词部分反转，遇到空格，则判断出一个单词结束
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			begin = i;
			while (str[i] && str[i] != ' ')
			{
				end = i;
				i++;
			}
			if (str[i] == '\0') //字符串的结束符
			{
				i--;
			}
		}
		while (end > begin)
		{
			temp = str[begin];
			str[begin] = str[end];
			str[end] = temp;
			end --;
			begin ++;
		}
		i ++;
	}
	cout << " string = " << str << endl;
	return str;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "I come from Tianjin.";
	strReverse(str);
	return 0;
}