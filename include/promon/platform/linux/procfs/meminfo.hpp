#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>

namespace promon::linux_backend::procfs {

struct MemInfo {
    std::uint64_t mem_total_kb = 0;
    std::uint64_t mem_free_kb = 0;
    std::uint64_t mem_available_kb = 0;

    std::uint64_t buffers_kb = 0;
    std::uint64_t cached_kb = 0;
    std::uint64_t swap_cached_kb = 0;

    std::uint64_t active_kb = 0;
    std::uint64_t inactive_kb = 0;
    std::uint64_t active_file_kb = 0;
    std::uint64_t inactive_file_kb = 0;

    std::uint64_t dirty_kb = 0;
    std::uint64_t writeback_kb = 0;

    std::uint64_t swap_total_kb = 0;
    std::uint64_t swap_free_kb = 0;

    std::uint64_t slab_kb = 0;
    std::uint64_t s_reclaimable_kb = 0;
    std::uint64_t s_unreclaim_kb = 0;
};

std::optional<MemInfo> read_meminfo(const std::filesystem::path& path = "/proc/meminfo");

} // namespace promon::linux_backend::procfs
