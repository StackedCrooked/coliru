#include <stdio.h>
int main(void)
{
    printf("short的长度: %lu,unsigned short的长度: %lu\n", sizeof(short), sizeof(unsigned short));
	printf("int的长度: %lu, unsigned int的长度: %lu\n", sizeof(int), sizeof(unsigned int));
	printf("long的长度: %lu, unsigned long的长度: %lu\n", sizeof(long), sizeof(unsigned long));
	printf("long long的长度: %lu, unsigned long long的长度: %lu\n", sizeof(long long), sizeof(unsigned long long));
    //声明一个int型变量var_int，一个unsigned int型变量var_uint
    int var_int;
    int var_uint;
    //令var_int等于2147483647(也就是2^31-1)
    var_int = 2147483647;
    printf("var_int = %d\n", var_int);
    //令var_int等于2147483648(也就是2^31)
    var_int = 2147483648;
    printf("var_int = %d\n", var_int);
    //会发现编译器给出警告表明var_int溢出，因为int是一个32位的数，有符号型最大为2^31-1
    //令var_uint = var_int
    var_uint = var_int;
    printf("var_uint = %u\n", var_uint);
    //当然也可以给var_int用16进制的数赋值
    var_int = 0x10;
    printf("var_int = %d\n", var_int);
    //用u后缀将一个数强制表明为无符号数
    var_uint = 35u;
    printf("var_uint = %u\n", var_uint);
    //但是因为var_uint本身就是无符号变量，所以赋值用的数是否加后缀u都无所谓
    var_uint = 35; //后面没有后缀u
    printf("var_uint = %u\n", var_uint);
    //但是在这种情况下就需要后缀
    //printf中用ld表明一个long int，但是后面的参数却是12345，是int
    //此时编译器应当会有一个警告
    printf("12345=%ld\n", 12345);
    //应当将12345声明为long型
    printf("12345=%ld\n", 12345L);
	return 0;
}