#pragma once

#include "promon/core/types.hpp"

#include <chrono>
#include <vector>

namespace promon {

struct Snapshot {
    std::chrono::steady_clock::time_point timestamp;
    SystemMemory memory;
    VmStat vmstat;
    CpuStat cpu;
    std::vector<ProcessInfo> processes;
};

} // namespace promon
