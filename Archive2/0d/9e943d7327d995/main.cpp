#include <atomic>
const int num_mailboxes = 32;
std::atomic<int> mailbox[num_mailboxes];
 
 int main(int argc, char* argv[])
 {
    // The writer threads update non-atomic shared data and then update mailbox[i] as follows
     //std::atomic_store_explicit(&mailbox[0], 10, std::memory_order_release);
     
     int my_id = 0;
    // Reader thread needs to check all mailbox[i], but only needs to sync with one
     for (int i = 0; i < num_mailboxes; ++i) {
        if (std::atomic_load_explicit(&mailbox[i],  std::memory_order_relaxed) == my_id) {
            std::atomic_thread_fence(std::memory_order_acquire); // synchronize with just one writer
            //do_work(i); // guaranteed to observe everything done in the writer thread before
                        // the atomic_store_explicit()
        }
     }
 }