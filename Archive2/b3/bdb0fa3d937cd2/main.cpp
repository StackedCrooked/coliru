template<typename... Sig, typename Key, typename... Args>
void set_function(Key&& key, Args&&... args) = delete;

int overloaded();

int main() {
    set_function<int>("overloaded", overloaded);
}