#include <thread>
#include <iostream>

using namespace std;

struct Parameter {};

namespace {
    void write_to_disk(const Parameter&) {}
}

class Exporter {
   public:
    Exporter(const Parameter& parameter);
    virtual ~Exporter();
    void save() const;

   private:
    Parameter parameter;
};

Exporter::Exporter(const Parameter& parameter) {
    this->parameter = parameter;
}

void Exporter::save() const {
    thread(write_to_disk, this->parameter).detach();
}

Exporter::~Exporter() {
}


int main() {
    Parameter par;
    Exporter e(par);
    e.save();
    std::this_thread::sleep_for(std::chrono::seconds{1});
}
