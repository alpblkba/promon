#pragma once

#include <cstdint>
#include <optional>

namespace promon::macos_backend::mach {

struct HostMemory {
    std::uint64_t page_size = 0;

    std::uint64_t free_pages = 0;
    std::uint64_t active_pages = 0;
    std::uint64_t inactive_pages = 0;
    std::uint64_t wired_pages = 0;
    std::uint64_t speculative_pages = 0;
    std::uint64_t compressor_pages = 0;

    std::uint64_t faults = 0;
    std::uint64_t cow_faults = 0;
    std::uint64_t pageins = 0;
    std::uint64_t pageouts = 0;
    std::uint64_t zero_fill_count = 0;
    std::uint64_t reactivations = 0;
    std::uint64_t purges = 0;
};

std::optional<HostMemory> read_host_memory();

} // namespace promon::macos_backend::mach
