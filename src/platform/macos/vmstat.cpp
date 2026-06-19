#include "promon/platform/macos/vmstat.hpp"

#include "promon/platform/macos/mach/host_memory.hpp"

namespace promon::macos_backend {

VmStat read_vmstat() {
    VmStat stat;

    const auto memory = mach::read_host_memory();

    if (!memory) {
        return stat;
    }

    // macOS does not expose Linux /proc/vmstat counters directly.
    // This maps Mach VM counters into the closest shared model fields.
    stat.pgfault = memory->faults;
    stat.pgmajfault = memory->pageins;

    stat.pswpin = memory->pageins;
    stat.pswpout = memory->pageouts;

    return stat;
}

} // namespace promon::macos_backend
