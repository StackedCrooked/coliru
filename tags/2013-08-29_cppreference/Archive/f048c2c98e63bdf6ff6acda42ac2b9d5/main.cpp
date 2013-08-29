template<typename T> T from_string(std::string);
template<> int from_string<int>(std::string str) {
    return std::stoi(str);
}

// Etc

int main() {
    auto x = from_string<std::int64_t>("09808080");