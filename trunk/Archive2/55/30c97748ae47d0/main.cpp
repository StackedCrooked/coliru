#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <type_traits>
#include <utility>

template<typename Data, uint64_t queueSize>
class MTStack
{
public:
    MTStack() :
      m_produceHead{pointer{&m_nodes[0], 0}},
      m_consumeHead{pointer{nullptr, 0}}
    {
        for(int i=0; i<queueSize-1; ++i)
        {
            m_nodes[i].m_idx = i;
            m_nodes[i].next(&m_nodes[i+1]);
        }
        m_nodes[queueSize-1].m_idx = queueSize - 1;
        m_nodes[queueSize-1].next(nullptr);
    }

    bool push(const Data& data)
    {
        // Pop the producer list.
        auto cell = pop(m_produceHead);
        if(!cell)
            return false;

        // At this point cell should point to a node that is not in any of the lists
        m_data[cell->m_idx] = data;

        // Push that node as the new head of the consumer list
        push(cell, m_consumeHead);
        return true;
    }

    bool pop(Data& data)
    {
        // Pop the consumer list
        auto cell = pop(m_consumeHead);
        if(!cell)
            return false;

        // At this point cell should point to a node that is not in any of the lists
        data = m_data[cell->m_idx];

        // Push that node as the new head of the producer list
        push(cell, m_produceHead);
        return true;
    };

private:
    class CellNode
    {
        std::atomic<CellNode*> m_next;
    public:
        uint64_t m_idx;

        void next(CellNode* ptr) {
            m_next.store(ptr, std::memory_order_relaxed);
        }
        CellNode* next() const {
            return m_next;
        }
    };

    class pointer {
        CellNode* m_ptr;
        unsigned  m_version;
    public:
        pointer() = default;
        pointer(CellNode* ptr, unsigned version) :
          m_ptr{ptr}, m_version{version} {}

        operator CellNode* () const { return m_ptr; }

        CellNode* operator -> () const {
            return m_ptr;
        }

        unsigned next_version() const {
            return m_version + 1;
        }
    };

    static CellNode* pop(std::atomic<pointer>& list) {
        auto head = list.load();
        while(head &&
              !list.compare_exchange_weak(head,
                                          pointer{head->next(),
                                                  head.next_version()})) {
            ;
        }
        return head;
    }

    static void push(CellNode* cell, std::atomic<pointer>& list) {
        auto head = list.load();
        do {
            cell->next(head);
        } while(!list.compare_exchange_weak(head,
                                            pointer{cell,
                                                    head.next_version()}));
    }

    std::atomic<pointer> m_produceHead;

    Data m_data[queueSize];

    // The nodes for the two lists
    CellNode m_nodes[queueSize];

    std::atomic<pointer> m_consumeHead;
};


namespace {
#if 0
const auto producer_spin_max = std::numeric_limits<std::uint64_t>::max();
const auto consumer_spin_max = producer_spin_max;
#else
const auto producer_spin_max = 1u << 12;
const auto consumer_spin_max = 1u << 8;
#endif

std::atomic<std::uint64_t> producer_spins;

template <typename Stack>
void producer(Stack& queue, int n) {
  auto total_spins = 0ull;
  for (auto i = 0; i < n; ++i) {
    auto spin_count = 0u;
    while (!queue.push(i)) {
      if (++spin_count == producer_spin_max) {
        total_spins += producer_spin_max;
        spin_count = 0u;
        std::this_thread::yield();
      }
    }
    total_spins += spin_count;
  }
  producer_spins += total_spins;
}

std::atomic<std::uint64_t> consumer_spins;

template <typename Stack>
int consumer(Stack& queue, std::atomic<bool> const& stop_flag) {
  auto total_spins = 0ull;
  auto count = 0;
  auto spin_count = 0u;
  for (;;) {
    int i;
    if (queue.pop(i)) {
      // std::cout << std::to_string(i) + ' ';
      ++count;
      total_spins += spin_count;
      spin_count = 0u;
    } else {
      if (stop_flag) {
        break;
      }
      if (++spin_count == consumer_spin_max) {
        total_spins += consumer_spin_max;
        spin_count = 0u;
        std::this_thread::yield();
      }
    }
  }
  consumer_spins += total_spins;
  return count;
}
} // anonymous namespace

int main() {
  MTStack<int, 32> q;
  std::atomic<bool> finished{false};

  auto consumers = std::array<std::future<int>, 4>{{}};
  for (auto& f : consumers) {
    f = std::async(std::launch::async, [&]{ return consumer(q, finished); });
  }

  auto producers = std::array<std::thread, 4>{{}};
  for (auto& t : producers) {
    t = std::thread([&]{ producer(q, (1 << 16)); });
  }

  for (auto& t : producers) {
    t.join();
  }

  finished = true;

  auto total = 0;
  for (auto& f : consumers) {
    total += f.get();
  }

  std::cout << "Total consumed: " << total << "\n"
               "Producer spins: " << producer_spins.load() << "\n"
               "Consumer spins: " << consumer_spins.load() << '\n';
}
