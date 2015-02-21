#include <utility>
#include <iostream>
struct Gizmo
{
    // Rule of Five members implemented
    ~Gizmo() { std::cout << "Gizmo destroyed\n"; }
};

Gizmo Frobnicate(const Gizmo& arg) { return arg; }

void ProcessGizmo(const Gizmo& arg, bool frobnicate)
{
    const Gizmo& local = frobnicate ? static_cast<const Gizmo&>(Frobnicate(arg)) : arg;
    // Perform some work on local
    (void) local;
    std::cout << "Processing\n";
}

int main(){
    Gizmo g;
    ProcessGizmo(g, true);
    std::cout << "Processed\n";
}