#include "gtest/gtest.h"

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
