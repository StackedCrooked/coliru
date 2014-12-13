// For open
#include <sys/stat.h>
#include <fcntl.h>

// For close
#include <unistd.h>

// For unique_ptr
#include <memory>

    struct handle_wrapper {

        handle_wrapper() noexcept : handle(-1) {}
        explicit handle_wrapper(int h) noexcept : handle(h) {}
        handle_wrapper(std::nullptr_t)  noexcept : handle_wrapper() {}

        int operator *() const noexcept { return handle; }
        explicit operator bool() const noexcept { return *this != nullptr; }

        friend bool operator!=(const handle_wrapper& a, const handle_wrapper& b) noexcept {
            return a.handle != b.handle;
        }

        friend bool operator==(const handle_wrapper& a, const handle_wrapper& b) noexcept {
            return a.handle == b.handle;
        }

        int handle;
    };


    struct posix_close
    {
        using pointer = handle_wrapper;
        void operator()(pointer fd)
        {
            close(*fd);
        }
    };

    int
    main()
    {
        std::unique_ptr<int, posix_close> p(handle_wrapper(open("testing", O_CREAT)));
        int fd = *p.get();
    }
