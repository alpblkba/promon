#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace promon::macos_backend::libproc_reader {

struct ProcessInfoRaw {
    int pid = -1;
    int ppid = -1;
    int uid = -1;
    int gid = -1;

    std::string name;
    std::string path;

    std::uint64_t virtual_size_bytes = 0;
    std::uint64_t resident_size_bytes = 0;

    std::uint64_t user_time_ns = 0;
    std::uint64_t system_time_ns = 0;

    std::uint64_t faults = 0;
    std::uint64_t pageins = 0;
    std::uint64_t cow_faults = 0;
};

std::optional<ProcessInfoRaw> read_process_info(int pid);

} // namespace promon::macos_backend::libproc_reader
