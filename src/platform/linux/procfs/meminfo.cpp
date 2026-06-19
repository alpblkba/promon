#include "promon/platform/linux/procfs/meminfo.hpp"

#include "promon/platform/linux/procfs/reader.hpp"

#include <sstream>
#include <string>

namespace promon::linux_backend::procfs {

namespace {

void assign_field(MemInfo& info, const std::string& key, std::uint64_t value_kb) {
    if (key == "MemTotal:") {
        info.mem_total_kb = value_kb;
    } else if (key == "MemFree:") {
        info.mem_free_kb = value_kb;
    } else if (key == "MemAvailable:") {
        info.mem_available_kb = value_kb;
    } else if (key == "Buffers:") {
        info.buffers_kb = value_kb;
    } else if (key == "Cached:") {
        info.cached_kb = value_kb;
    } else if (key == "SwapCached:") {
        info.swap_cached_kb = value_kb;
    } else if (key == "Active:") {
        info.active_kb = value_kb;
    } else if (key == "Inactive:") {
        info.inactive_kb = value_kb;
    } else if (key == "Active(file):") {
        info.active_file_kb = value_kb;
    } else if (key == "Inactive(file):") {
        info.inactive_file_kb = value_kb;
    } else if (key == "Dirty:") {
        info.dirty_kb = value_kb;
    } else if (key == "Writeback:") {
        info.writeback_kb = value_kb;
    } else if (key == "SwapTotal:") {
        info.swap_total_kb = value_kb;
    } else if (key == "SwapFree:") {
        info.swap_free_kb = value_kb;
    } else if (key == "Slab:") {
        info.slab_kb = value_kb;
    } else if (key == "SReclaimable:") {
        info.s_reclaimable_kb = value_kb;
    } else if (key == "SUnreclaim:") {
        info.s_unreclaim_kb = value_kb;
    }
}

} // namespace

std::optional<MemInfo> read_meminfo(const std::filesystem::path& path) {
    const auto lines = read_lines(path);

    if (lines.empty()) {
        return std::nullopt;
    }

    MemInfo info;

    for (const auto& line : lines) {
        std::istringstream stream(line);

        std::string key;
        std::uint64_t value_kb = 0;
        std::string unit;

        stream >> key >> value_kb >> unit;

        if (key.empty()) {
            continue;
        }

        assign_field(info, key, value_kb);
    }

    return info;
}

} // namespace promon::linux_backend::procfs
