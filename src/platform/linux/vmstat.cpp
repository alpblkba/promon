#include "promon/platform/linux/vmstat.hpp"

#include "promon/platform/linux/procfs/vmstat.hpp"

namespace promon::linux_backend {

VmStat read_vmstat() {
    const auto vmstat = procfs::read_vmstat_file();

    if (!vmstat) {
        return {};
    }

    return *vmstat;
}

} // namespace promon::linux_backend
