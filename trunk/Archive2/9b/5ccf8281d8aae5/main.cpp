#include "gtest/gtest.h"

// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp: In instantiation of 'void TestProducerConsumer_testProduceDone_Test<gtest_TypeParam_>::TestBody() [with gtest_TypeParam_ = TestProducerConsumer<std::pair<long unsigned int, long unsigned int> >]':
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:59:1:   required from here
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:55:32: error: cannot declare variable 'v' to be of abstract type 'TestProducerConsumer<std::pair<long unsigned int, long unsigned int> >'
//      typename Queue::value_type v;
//                                 ^
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:9:7: note:   because the following virtual functions are pure within 'TestProducerConsumer<std::pair<long unsigned int, long unsigned int> >':
//  class TestProducerConsumer : public ::testing::Test
//        ^
// In file included from /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:1:0:
// /data/doug/code/worldgen/worldgen-build/gtest/include/gtest/gtest.h:422:16: note:     virtual void testing::Test::TestBody()
//    virtual void TestBody() = 0;
//                 ^
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp: In instantiation of 'void TestProducerConsumer_testProduceDone_Test<gtest_TypeParam_>::TestBody() [with gtest_TypeParam_ = TestProducerConsumer<long int>]':
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:59:1:   required from here
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:55:32: error: cannot declare variable 'v' to be of abstract type 'TestProducerConsumer<long int>'
//      typename Queue::value_type v;
//                                 ^
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:9:7: note:   because the following virtual functions are pure within 'TestProducerConsumer<long int>':
//  class TestProducerConsumer : public ::testing::Test
//        ^
// In file included from /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:1:0:
// /data/doug/code/worldgen/worldgen-build/gtest/include/gtest/gtest.h:422:16: note: 	virtual void testing::Test::TestBody()
//    virtual void TestBody() = 0;
//                 ^
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp: In instantiation of 'void TestProducerConsumer_testProduceDone_Test<gtest_TypeParam_>::TestBody() [with gtest_TypeParam_ = TestProducerConsumer<long unsigned int>]':
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:59:1:   required from here
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:55:32: error: cannot declare variable 'v' to be of abstract type 'TestProducerConsumer<long unsigned int>'
//      typename Queue::value_type v;
//                                 ^
// /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:9:7: note:   because the following virtual functions are pure within 'TestProducerConsumer<long unsigned int>':
//  class TestProducerConsumer : public ::testing::Test
//        ^
// In file included from /data/doug/code/worldgen/worldgen/test/testproducerconsumer.cpp:1:0:
// /data/doug/code/worldgen/worldgen-build/gtest/include/gtest/gtest.h:422:16: note: 	virtual void testing::Test::TestBody()
//    virtual void TestBody() = 0;
//                 ^

//#include "producerconsumer.h"
template<typename T>
class ProducerConsumer
{
public:
    typedef T value_type;
    bool pop(T& item);
};

#include <thread>
#include <cstdint>
#include <utility>



// From 

template<typename T>
class TestProducerConsumer : public ::testing::Test
{
public:
    typedef T value_type;
    typedef ProducerConsumer<T> type;
};

typedef ::testing::Types<
    TestProducerConsumer<char>,
    TestProducerConsumer<char16_t>,
    TestProducerConsumer<char32_t>,
    TestProducerConsumer<std::uint8_t>,
    TestProducerConsumer<std::int8_t>,
    TestProducerConsumer<std::uint16_t>,
    TestProducerConsumer<std::int16_t>,
    TestProducerConsumer<std::uint32_t>,
    TestProducerConsumer<std::int32_t>,
    TestProducerConsumer<std::uint64_t>,
    TestProducerConsumer<std::int64_t>,
    TestProducerConsumer<std::pair<std::uint64_t, std::uint64_t>>
> TestTypes;

TYPED_TEST_CASE(TestProducerConsumer, TestTypes);

void runPair(std::function<void()> a, std::function<void()> b)
{
    auto x = std::thread(a);
    auto y = std::thread(b);
    x.join();
    y.join();
}

TYPED_TEST(TestProducerConsumer, testConstruct)
{
    typename TestFixture::type pc(16);
}

TYPED_TEST(TestProducerConsumer, test)
{
    typename TestFixture::type pc(1);
}

TYPED_TEST(TestProducerConsumer, testProduceDone)
{
    typedef typename TestFixture::type Queue;
    Queue pc(1);
    typename Queue::value_type v;

    pc.pushDone();
    ASSERT_FALSE(pc.pop(v));
}
