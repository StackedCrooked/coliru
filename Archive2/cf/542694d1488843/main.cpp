/*
 * =====================================================================================
 *
 *       Filename:  vpAddr.cpp
 *
 *    Description:  Virtual to Physical address translation
 *
 *        Version:  1.0
 *        Created:  Tuesday 02 December 2014 06:56:41  IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Sayantan (war10ck), skb655952@gmail.com
 *   Organization:  codeManush
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

#ifndef DEFAULT_VALUE
    #define DEFAULT_VALUE 10
#endif

#ifndef THREAD_MAX
    #define THREAD_MAX 2
#endif

auto genVAddr(int max, int min) -> int
{
    /* (SB) Function to generate virtual address */
    decltype(max) retVal = (int)(rand() % (max - min + 1) + min);
    return retVal;
}

void addrTranslate(std::vector<int>& inpVec)
{
    /* (SB) Function to read nxt->vAddr() from input container and translate to physical address */
}

int main(int argc, char *argv[])
{
    std::cout<<"Working!!!\n";
    std::vector<int> genVAddrList;

    /* (SB) Checking if the threading is working fine or not */
    srand(time(NULL));
    std::thread procThread[THREAD_MAX];
    int vAddr;

    procThread[0] = std::thread([&]{vAddr = genVAddr(8, 1);});
    procThread[1] = std::thread(addrTranslate, std::ref(genVAddrList));
    std::cout<<"Running main() function : "<<vAddr<<std::endl;
    /* (SB) sync the threads before exiting */
    procThread[0].join();
    procThread[1].join();

    procThread[0] = std::thread(genVAddr, 8, 1);
    procThread[1] = std::thread(addrTranslate);

    procThread[0].join();
    procThread[1].join();
    return EXIT_SUCCESS;
}