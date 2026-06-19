#include "promon/core/rate.hpp"

#include <algorithm>
#include <cstdint>

namespace promon {

namespace {

double counter_rate(std::uint64_t previous, std::uint64_t current, double elapsed_seconds) {
    if (elapsed_seconds <= 0.0) {
        return 0.0;
    }

    // Kernel counters should normally be monotonic. If something resets or wraps
    // in a small test environment, avoid producing negative-looking nonsense.
    if (current < previous) {
        return 0.0;
    }

    return static_cast<double>(current - previous) / elapsed_seconds;
}

} // namespace

VmStatRate compute_vmstat_rate(const VmStat& previous, const VmStat& current, double elapsed_seconds) {
    VmStatRate rate;

    rate.pgfault_per_sec = counter_rate(previous.pgfault, current.pgfault, elapsed_seconds);
    rate.pgmajfault_per_sec = counter_rate(previous.pgmajfault, current.pgmajfault, elapsed_seconds);

    rate.pgscan_kswapd_per_sec = counter_rate(previous.pgscan_kswapd, current.pgscan_kswapd, elapsed_seconds);
    rate.pgscan_direct_per_sec = counter_rate(previous.pgscan_direct, current.pgscan_direct, elapsed_seconds);
    rate.pgscan_per_sec = rate.pgscan_kswapd_per_sec + rate.pgscan_direct_per_sec;

    rate.pgsteal_kswapd_per_sec = counter_rate(previous.pgsteal_kswapd, current.pgsteal_kswapd, elapsed_seconds);
    rate.pgsteal_direct_per_sec = counter_rate(previous.pgsteal_direct, current.pgsteal_direct, elapsed_seconds);
    rate.pgsteal_per_sec = rate.pgsteal_kswapd_per_sec + rate.pgsteal_direct_per_sec;

    rate.pswpin_per_sec = counter_rate(previous.pswpin, current.pswpin, elapsed_seconds);
    rate.pswpout_per_sec = counter_rate(previous.pswpout, current.pswpout, elapsed_seconds);

    return rate;
}

} // namespace promon
