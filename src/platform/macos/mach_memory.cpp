#include "promon/platform/macos/mach_memory.hpp"

#include "promon/platform/macos/mach/host_memory.hpp"
#include "promon/platform/macos/sysctl/hw_memsize.hpp"

namespace promon::macos_backend {

namespace {

std::uint64_t pages_to_kib(std::uint64_t pages, std::uint64_t page_size) {
    return (pages * page_size) / 1024;
}

} // namespace

SystemMemory read_system_memory() {
    SystemMemory memory;

    const auto total_bytes = sysctl_reader::read_hw_memsize_bytes();
    const auto host_memory = mach::read_host_memory();

    if (total_bytes) {
        memory.total_kb = *total_bytes / 1024;
    }

    if (!host_memory) {
        return memory;
    }

    const auto page_size = host_memory->page_size;

    memory.free_kb = pages_to_kib(host_memory->free_pages, page_size);

    // macOS does not expose Linux-style MemAvailable/Cached directly.
    // This is a practical approximation for a first diagnostic view.
    const auto inactive_kb = pages_to_kib(host_memory->inactive_pages, page_size);
    const auto speculative_kb = pages_to_kib(host_memory->speculative_pages, page_size);

    memory.available_kb = memory.free_kb + inactive_kb + speculative_kb;
    memory.cached_kb = inactive_kb + speculative_kb;

    return memory;
}

} // namespace promon::macos_backend
