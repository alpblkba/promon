#pragma once

#include "promon/core/types.hpp"

#include <chrono>
#include <optional>
#include <vector>

namespace promon {

struct Snapshot {
    std::chrono::steady_clock::time_point timestamp;
    SystemMemory memory;
    VmStat vmstat;
    std::optional<VmStatRate> vmstat_rate;
    CpuStat cpu;
    std::vector<ProcessInfo> processes;
};

} // namespace promon
