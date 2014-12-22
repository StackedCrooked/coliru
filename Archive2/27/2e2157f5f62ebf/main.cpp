#include <chrono>
#include <thread>

using namespace std;

struct Parameter {};

namespace {
    void write_to_disk(const Parameter&) {}
}

struct Exporter {
    void save() const;
    Parameter parameter;
};

void Exporter::save() const {
    thread(write_to_disk, this->parameter).detach();
}

int main() {
    Exporter e;
    e.save();
    std::this_thread::sleep_for(std::chrono::seconds{1});
}
