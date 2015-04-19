#include "stdafx.h"  
#include<stdlib.h>  
#include<crtdbg.h>  
#include <iostream>  
// 内存泄露检测机制  
#define _CRTDBG_MAP_ALLOC   
#ifdef _DEBUG  
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)  
#endif  
 
// 自定义异常类  
class MyExcepction  
{  
public:  
 
        // 构造函数,参数为错误代码  
        MyExcepction(int errorId)  
        {  
            // 输出构造函数被调用信息  
            std::cout << "MyExcepction is called" << std::endl;  
            m_errorId = errorId;  
        }  
 
        // 拷贝构造函数  
        MyExcepction( MyExcepction& myExp)  
        {  
            // 输出拷贝构造函数被调用信息  
            std::cout << "copy construct is called" << std::endl;  
            this->m_errorId = myExp.m_errorId;  
        }  
 
       ~MyExcepction()  
        {  
            // 输出析构函数被调用信息  
            std::cout << "~MyExcepction is called" << std::endl;  
        }  
 
       // 获取错误码  
        int getErrorId()  
        {  
            return m_errorId;  
        }  
 
private:      
        // 错误码  
        int m_errorId;  
};  
 
int main(int argc, char* argv[])  
{  
        // 内存泄露检测机制  
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );  
 
        // 可以改变错误码,以便抛出不同的异常进行测试  
        int throwErrorCode = 110;  
 
       std::cout << " input test code :" << std::endl;  
       std::cin >> throwErrorCode;  
 
       try 
       {  
            if ( throwErrorCode == 110)  
            {  
                MyExcepction myStru(110);  
 
                // 抛出对象的地址 -> 由catch( MyExcepction*    pMyExcepction) 捕获  
                // 这里该对象的地址抛出给catch语句,不会调用对象的拷贝构造函数  
                // 传地址是提倡的做法,不会频繁地调用该对象的构造函数或拷贝构造函数  
                // catch语句执行结束后,myStru会被析构掉  
                throw    &myStru;      
            }  
            else if ( throwErrorCode == 119 )  
            {  
                MyExcepction myStru(119);  
 
                // 抛出对象,这里会通过拷贝构造函数创建一个临时的对象传出给catch  
                // 由catch( MyExcepction    myExcepction) 捕获  
                // 在catch语句中会再次调用通过拷贝构造函数创建临时对象复制这里传过去的对象  
                // throw结束后myStru会被析构掉  
                throw    myStru;      
             }  
             else if ( throwErrorCode == 120 )  
             {  
                  // 不提倡这样的抛出方法  
                  // 这样做的话,如果catch( MyExcepction*    pMyExcepction)中不执行delete操作则会发生内存泄露  
 
                  // 由catch( MyExcepction*    pMyExcepction) 捕获  
                  MyExcepction * pMyStru = new MyExcepction(120);   
                  throw pMyStru;      
             }  
             else 
             {  
                  // 直接创建新对象抛出  
                  // 相当于创建了临时的对象传递给了catch语句  
                  // 由catch接收时通过拷贝构造函数再次创建临时对象接收传递过去的对象  
                  // throw结束后两次创建的临时对象会被析构掉  
                   throw MyExcepction(throwErrorCode);      
             }      
        }  
        catch( MyExcepction*    pMyExcepction)  
        {  
             // 输出本语句被执行信息  
               std::cout << "执行了 catch( MyExcepction*    pMyExcepction) " << std::endl;  
 
             // 输出错误信息  
               std::cout << "error Code : " << pMyExcepction->getErrorId()<< std::endl;  
 
            // 异常抛出的新对象并非创建在函数栈上，而是创建在专用的异常栈上,不需要进行delete  
            //delete pMyExcepction;  
        }  
        catch ( MyExcepction myExcepction)  
        {  
            // 输出本语句被执行信息  
            std::cout << "执行了 catch ( MyExcepction myExcepction) " << std::endl;  
 
            // 输出错误信息  
            std::cout << "error Code : " << myExcepction.getErrorId()<< std::endl;  
        }  
        catch(...)  
        {  
             // 输出本语句被执行信息  
             std::cout << "执行了 catch(...) " << std::endl;  
 
             // 处理不了,重新抛出给上级  
             throw ;  
        }  
 
        // 暂停  
        int temp;  
        std::cin >> temp;  
 
       return 0;  
}