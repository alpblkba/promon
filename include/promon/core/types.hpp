#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace promon {

struct SystemMemory {
    std::uint64_t total_kb = 0;
    std::uint64_t available_kb = 0;
    std::uint64_t free_kb = 0;
    std::uint64_t cached_kb = 0;
    std::uint64_t buffers_kb = 0;
    std::uint64_t swap_total_kb = 0;
    std::uint64_t swap_free_kb = 0;
};

struct VmStat {
    std::uint64_t pgfault = 0;
    std::uint64_t pgmajfault = 0;
    std::uint64_t pgscan_kswapd = 0;
    std::uint64_t pgscan_direct = 0;
    std::uint64_t pgsteal_kswapd = 0;
    std::uint64_t pgsteal_direct = 0;
    std::uint64_t pswpin = 0;
    std::uint64_t pswpout = 0;
};

struct VmStatRate {
    double pgfault_per_sec = 0.0;
    double pgmajfault_per_sec = 0.0;

    double pgscan_kswapd_per_sec = 0.0;
    double pgscan_direct_per_sec = 0.0;
    double pgscan_per_sec = 0.0;

    double pgsteal_kswapd_per_sec = 0.0;
    double pgsteal_direct_per_sec = 0.0;
    double pgsteal_per_sec = 0.0;

    double pswpin_per_sec = 0.0;
    double pswpout_per_sec = 0.0;
};

struct CpuStat {
    std::uint64_t user = 0;
    std::uint64_t nice = 0;
    std::uint64_t system = 0;
    std::uint64_t idle = 0;
    std::uint64_t iowait = 0;
    std::uint64_t irq = 0;
    std::uint64_t softirq = 0;
    std::uint64_t steal = 0;
};

struct ProcessInfo {
    int pid = -1;
    int ppid = -1;
    std::string name;
    char state = '?';

    std::uint64_t vm_size_kb = 0;
    std::uint64_t vm_rss_kb = 0;
    std::uint64_t vm_swap_kb = 0;

    std::uint64_t minor_faults = 0;
    std::uint64_t major_faults = 0;

    std::uint64_t voluntary_context_switches = 0;
    std::uint64_t involuntary_context_switches = 0;

    int threads = 0;
};

struct ThreadInfo {
    int tid = -1;
    std::string name;
    char state = '?';
    std::uint64_t user_ticks = 0;
    std::uint64_t system_ticks = 0;
    std::uint64_t voluntary_context_switches = 0;
    std::uint64_t involuntary_context_switches = 0;
};

} // namespace promon
