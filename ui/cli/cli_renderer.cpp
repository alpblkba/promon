#include "cli_renderer.hpp"

#include <cstdint>
#include <iomanip>
#include <iostream>

namespace promon::ui::cli {

namespace {

double kib_to_gib(std::uint64_t kib) {
    return static_cast<double>(kib) / 1024.0 / 1024.0;
}

void render_memory(const SystemMemory& memory) {
    const auto used_kb =
        memory.total_kb > memory.available_kb
            ? memory.total_kb - memory.available_kb
            : 0;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "memory\n";
    std::cout << "  total      " << kib_to_gib(memory.total_kb) << " GiB\n";
    std::cout << "  used       " << kib_to_gib(used_kb) << " GiB\n";
    std::cout << "  available  " << kib_to_gib(memory.available_kb) << " GiB\n";
    std::cout << "  free       " << kib_to_gib(memory.free_kb) << " GiB\n";
    std::cout << "  cached     " << kib_to_gib(memory.cached_kb) << " GiB\n";
}

} // namespace

void CliRenderer::render(const Snapshot& snapshot) {
    std::cout << "promon v0\n\n";
    render_memory(snapshot.memory);
}

} // namespace promon::ui::cli
