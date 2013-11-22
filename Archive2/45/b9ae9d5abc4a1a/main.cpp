#include <boost/variant.hpp>
#include <vector>
#include <stdint.h>
#include <string.h>


namespace Detail {
    

struct RangeData
{
    RangeData(const uint8_t* b, const uint8_t* e) : b(b), e(e) {}    
    RangeData(uint8_t* b, std::size_t size) : b(b), e(b + size) {}
    
    std::size_t size() const { return e - b; }
    
    const uint8_t* b;
    const uint8_t* e;
};


// OwningRangeData range copies the data into new memory.
// TODO: use operator new[]?
struct OwningRangeData : RangeData
{  
    OwningRangeData(const uint8_t* b, std::size_t length) : RangeData(static_cast<uint8_t*>(malloc(length)), length)
    {
        memcpy(const_cast<uint8_t*>(this->b), b, size());
    }
    
    OwningRangeData(const uint8_t* b, const uint8_t* e) : OwningRangeData(b, e - b) {} // delegate
    
    ~OwningRangeData()
    {
        free(const_cast<uint8_t*>(b));
        b = e = nullptr;
    }
    
    OwningRangeData(const OwningRangeData& rhs) : OwningRangeData(rhs.b, rhs.e) {} // delegate
    
    OwningRangeData& operator=(OwningRangeData rhs) // copy/swap
    {
        std::swap(b, rhs.b);
        std::swap(e, rhs.e);
        return *this;
    }
    
    OwningRangeData(OwningRangeData&& rhs) : RangeData(rhs.b, rhs.e) // copy data
    {
        rhs.b = rhs.e = nullptr; // invalidate rhs
    }
    
    OwningRangeData& operator=(OwningRangeData&& rhs)
    {
        this->RangeData::operator=(rhs); // copy members
        rhs.b = rhs.e = nullptr;  // invalidate rhs
        return *this;
    }
};


} // namespace Detail



struct ByteRange
{
    struct Refer{};
    struct Copy{};
    
    ByteRange(const uint8_t* b, const uint8_t* e, Refer) : impl(RangeData(b, e)) {}
    ByteRange(const uint8_t* b, const uint8_t* e, Copy) : impl(OwningRangeData(b, e)) {}
    
    ByteRange(const ByteRange& rhs) : impl(rhs.impl) {}
    ByteRange& operator=(const ByteRange&) = default;
    ByteRange(ByteRange&& rhs) : impl(std::move(rhs.impl)) {}
    
    bool owns() const
    {
        return !!boost::get<OwningRangeData>(&impl);
    }    

    const uint8_t* data() const
    {
        return obj().b;
    }

    const uint8_t* begin() const
    {
        return data();
    }
    
    const uint8_t* end() const
    {
        return obj().e;
    }
    
    std::size_t size() const
    {
        return obj().size();
    }

    
private:
    using RangeData = Detail::RangeData;
    using OwningRangeData = Detail::OwningRangeData;

    const RangeData& obj() const
    {
        if (auto p = boost::get<RangeData>(&impl)) return *p;
        return boost::get<OwningRangeData>(impl);
    }

    boost::variant<OwningRangeData, RangeData> impl;
};


bool are_equal(const ByteRange& lhs, const ByteRange& rhs)
{
    return lhs.size() == rhs.size() && !memcmp(lhs.begin(), rhs.begin(), rhs.size());
}


bool are_identical(const ByteRange& lhs, const ByteRange& rhs)
{
    return lhs.begin() == rhs.begin() && lhs.end() == rhs.end();
}


#define VERIFY(name) std::cout << ((name) ? "PASS: " : "FAIL: ") << #name << std::endl;


int main()
{
    std::vector<uint8_t> test = { 'a', 'b', 'c' };
    
    
    // test non-owning range
    ByteRange alias(test.data(), test.data() + test.size(), ByteRange::Refer{});    
    auto alias_copy = alias;
    VERIFY(!alias.owns() && !alias_copy.owns());
    VERIFY(are_equal(alias, alias_copy) && are_identical(alias, alias_copy));
    
    
    // test owning range
    ByteRange owner(test.data(), test.data() + test.size(), ByteRange::Copy{});
    auto owner_copy = owner;
    VERIFY(owner.owns() && owner_copy.owns());
    VERIFY(are_equal(owner, owner_copy) && !are_identical(owner, owner_copy));
    
    
    // test cross-type assignments
    VERIFY((alias = owner, alias.owns()));
    VERIFY((owner = alias_copy, !owner.owns()));
}
