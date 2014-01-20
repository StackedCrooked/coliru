#include <nonius/benchmarks.h++>

#include <string>

NONIUS_BENCHMARK("to_string ints") -> std::string {
    return std::to_string(42);
}

NONIUS_BENCHMARK("to_string doubles") -> std::string {
    return std::to_string(42.0);
}

// --- another TU ---

#include <nonius/benchmarks.h++>

#include <wtf/raytracer.hpp>

NONIUS_BENCHMARK("empty scene to bit bucket") -> void {
    wtf::scene s;
    wtf::null_output out;
    wtf::raytrace(scene, out);
}

// --- another TU ---

#include <nonius/main.h++>
