template<typename... Sig, typename Key, typename... Args>
void set_function(Key&& key, Args&&... args) = delete;

int overloaded();
int overloaded(int);

int main() {
    set_function<int>("overloaded", overloaded);
}