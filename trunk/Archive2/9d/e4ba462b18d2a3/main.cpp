
int main() {
    
    std::unique_lock<std::mutex> lock (some_mutex);
    {
        condition_variable.wait(lock, [](...));
        ...
        // is the lock re-acquired by condition variable released here?
    }
    ...
    // or here?
}
