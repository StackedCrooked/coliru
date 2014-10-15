#include <stdio.h>
int main()
{
    [=](void*a)->void{[=](void*a)->void{[&](void*a)mutable->void{[&](void*a)mutable->void{[=](void*a)->void{
	[&](void*a)->void{[&](void*a)->void{[&](void*a)mutable->void{[=](void*a)->void{[=](void*a)->void{[&](void*a)->
	void{[=](void*a)mutable->void{printf("%c",*(char*)a);delete(char*)a;}(new char(72));printf("%c",*(char*)a);delete(char*)a;return;}
	(new char(69));printf("%c",*(char*)a);delete(char*)a;return;}(new char(76));printf("%c",*(char*)a);delete(char*)a;}(new char
	(76));printf("%c",*(char*)a);delete(char*)a;return;}(new char(79));printf("%c",**(char**)&*&*&a);delete(char*)a;return;}
	(new char(95));printf("%c",*(char*)a);delete(char*)a;}(new char(87));printf("%c",*&*(char*)*&a);delete(char*) a;return;}(new
	char(79));printf("%c",*(char*)a);delete(char*)a;return;}(new char(82));printf("%c",*(char*)a);delete(char*)a;}(new char(76));
	printf("%c",**(char**)&a);delete(char*)a;return;}(new char(68));printf("%c",*(char*)a);delete(char*)a;}(new char(10));
}