#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <boost/iterator/iterator_facade.hpp>

class Message {};
class SpecificMessage {
public:
  SpecificMessage(const Message&) {}
};

class FileCache {
  std::vector<std::weak_ptr<Message>> messages_;

  // load the message with specified index into the cache
  std::shared_ptr<Message> load(std::size_t i) {
    assert(i < messages_.size());
    auto msg = messages_[i].lock();
    if (!msg) {
      std::cout << "    Cache miss: " << i << '\n';
      // "load" message from the file
      auto the_msg = std::unique_ptr<Message>{new Message{}};
      // Insert in the cache
      msg = std::shared_ptr<Message>{std::move(the_msg)};
      messages_[i] = msg;
    } else {
      std::cout << "    Cache hit: " << i << '\n';
    }
    return msg;
  }

public:
  class iterator : public boost::iterator_facade<iterator, Message, std::random_access_iterator_tag, Message&> {
    friend class boost::iterator_core_access;
    FileCache* fc_;
    std::size_t index_;
    mutable std::shared_ptr<Message> current_;

    bool valid() const {
      return fc_ && index_ <= fc_->messages_.size();
    }

    void expire() const {
      current_ = {};
    }

    Message& dereference() const {
      if (!current_) {
        assert(valid());
        current_ = fc_->load(index_);
      }
      return *current_;
    }

    bool equal(const iterator& other) const {
      assert(fc_ == other.fc_);
      return index_ == other.index_;
    }

    void increment() {
      expire();
      ++index_;
    }

    void decrement() {
      expire();
      --index_;
    }

    void advance(std::ptrdiff_t n) {
      expire();
      index_ += n;
    }

    std::ptrdiff_t distance_to(const iterator& other) const {
      return other.index_ - index_;
    }

  public:
    ~iterator() {
      expire();
    }

    iterator() : fc_{}, index_{} {}
    iterator(FileCache& fc, std::size_t i) :
      fc_{&fc}, index_{i} { assert(valid()); }
  };

  FileCache(std::string /* filename */) {
    // open the file, determine the number of contained messages "n"
    auto n = 4u;
    messages_.resize(n);
  }

  void expire() {
    // Cleanup expired cache entries (releases the control blocks for expired weak_ptrs)
    for (auto& w : messages_) {
      if (w.expired()) {
        w = {};
      }
    }
  }

  iterator begin() { return {*this, 0}; }
  iterator end() { return {*this, messages_.size()}; }
};

int main() {
  FileCache fc("file.bin");
  {
    auto counter = 0u;
    for (auto& m : fc) {
      std::cout << "Message " << counter++ << " @ " << &m << '\n';
      auto counter2 = 0u;
      for (auto& m2 : fc) {
        std::cout << "  Message " << counter2++ << " @ " << &m2 << '\n';
      }
    }
  }

  {
    // Move to Message #2
    auto pos = fc.begin() + 2;
    std::cout << "Message 2 has moved to " << &*pos << '\n';
    auto pos2 = fc.begin() + 2;
    std::cout << "Message 2 is still at " << &*pos2 << '\n';
    pos = {};
    auto pos3 = pos2;
    pos2 = {};
    std::cout << "Message 2 is *still* at " << &*pos3 << '\n';
    // Try deserializing as SpecificMessage
    SpecificMessage{*pos3};
  }
}
