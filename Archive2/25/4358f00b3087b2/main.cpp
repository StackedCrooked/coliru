#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <fstream>

struct DeblurImage {
    std::vector<uint8_t> data;
};

using MX = boost::mutex;
using CV = boost::condition_variable;

boost::shared_ptr<DeblurImage> readImage(std::string fname) 
{
    auto result = boost::make_shared<DeblurImage>();
    std::ifstream is(fname);
    std::copy(std::istreambuf_iterator<char>(is), {}, std::back_inserter(result->data));
    
    return result;
}

// SHARED STATE
boost::shared_ptr<DeblurImage> toDeblur;
//

void reader_thread(MX* deblurLock, CV* deblurCondition, CV* readCondition)
{
    boost::unique_lock<boost::mutex> lock(*deblurLock);

    //Wait until it's okay to read again.
    while(toDeblur != NULL)
        readCondition->wait(lock);

    toDeblur = readImage("test.cpp");

    std::cerr << "readImage notifying deblurCondition" << std::endl;
    //Notify the processing thread(s) that an image is ready.
    deblurCondition->notify_one();
}

void processing_thread(MX* deblurLock, CV* deblurCondition, CV* readCondition)
{
    //Wait for our condition variable.
    boost::unique_lock<boost::mutex> lock(*deblurLock);
    std::cerr << "processImage waiting for non-NULL image" << std::endl;
    while(toDeblur == NULL)
    {
        std::cerr << "processImage waiting for deblurCondition variable" << std::endl;
        deblurCondition->wait(lock);
    }

    readCondition->notify_one();
    std::cerr << "processImage(kernels, deblurP, toDeblur);\n";
}

int main()
{
    MX deblurLock;
    CV deblurCondition, readCondition;
    boost::thread_group tg;
    tg.create_thread([&] { int i = 2; while(i--) reader_thread(&deblurLock,     &deblurCondition, &readCondition); });
    tg.create_thread([&] { int i = 2; while(i--) processing_thread(&deblurLock, &deblurCondition, &readCondition); });

    tg.join_all();
}