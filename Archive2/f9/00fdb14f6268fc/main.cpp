#include <memory>

namespace styx {
    struct object {};

    class thread {
    public:
        thread(void const* instruction_ptr_arg);

        void resume();

    private:
        std::unique_ptr<object * []> evaluation_stack;
        object** evaluation_stack_top;

        std::unique_ptr<void const * []> return_stack;
        void const** return_stack_top;

        void const* instruction_ptr;
    };
}

#include <cstddef>

namespace {
    auto constexpr stack_size = static_cast<std::size_t>(64 * 1024);
}

styx::thread::thread(void const* instruction_ptr_arg)
    : evaluation_stack(new object* [stack_size]),
      evaluation_stack_top(evaluation_stack.get()),
      return_stack(new void const* [stack_size]),
      return_stack_top(return_stack.get()),
      instruction_ptr(instruction_ptr_arg) {}

[[gnu::noinline]] void styx::thread::resume() {
    asm volatile("movq %0, %%r13\n"
                 "movq %1, %%r14\n"
                 "movq %2, %%r15\n"
                 "callq *%3\n"
                 :
                 : "r"(&evaluation_stack_top), "r"(&return_stack_top),
                   "r"(&instruction_ptr), "r"(instruction_ptr));
}

#include <initializer_list>

namespace styx {
    enum class opcode {
        yield
    };

    template <typename OutputIt> OutputIt translate(opcode op, OutputIt it) {
        switch (op) {
        case opcode::yield:
            // leaq 4(%rip), %rax
            for (auto byte : { 0x48, 0x8d, 0x05, 0x04, 0x00, 0x00, 0x00 })
                *it++ = byte;

            // movq %rax, (%r15)
            for (auto byte : { 0x49, 0x89, 0x07 })
                *it++ = byte;

            // ret
            *it++ = 0xC3;
            break;
        }

        return it;
    }
}

#include <algorithm>
#include <iterator>
#include <sys/mman.h>
#include <vector>

int main() {
    std::vector<unsigned char> code;
    styx::translate(styx::opcode::yield, std::back_inserter(code));
    styx::translate(styx::opcode::yield, std::back_inserter(code));
    styx::translate(styx::opcode::yield, std::back_inserter(code));
    styx::translate(styx::opcode::yield, std::back_inserter(code));
    styx::translate(styx::opcode::yield, std::back_inserter(code));

    auto executable_code = static_cast<char*>(
        mmap(nullptr, code.size(), PROT_READ | PROT_WRITE | PROT_EXEC,
             MAP_PRIVATE | MAP_ANON, -1, 0));
    std::copy(code.begin(), code.end(), executable_code);

    styx::thread thread(executable_code);
    thread.resume();
    thread.resume();
    thread.resume();
    thread.resume();
    thread.resume();
    // thread.resume(); // uncomment to crash
    return 0;
}
