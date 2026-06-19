#pragma once

#include <cstdint>
#include <optional>

namespace promon::macos_backend::libproc_reader {

struct ProcessIoRaw {
    int pid = -1;
    std::uint64_t read_bytes = 0;
    std::uint64_t write_bytes = 0;
};

std::optional<ProcessIoRaw> read_process_io(int pid);

} // namespace promon::macos_backend::libproc_reader
