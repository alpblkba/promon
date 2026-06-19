#include "promon/platform/linux/procfs/vmstat.hpp"

#include "promon/platform/linux/procfs/reader.hpp"

#include <sstream>
#include <string>

namespace promon::linux_backend::procfs {

namespace {

void assign_field(VmStat& stat, const std::string& key, std::uint64_t value) {
    if (key == "pgfault") {
        stat.pgfault = value;
    } else if (key == "pgmajfault") {
        stat.pgmajfault = value;
    } else if (key == "pgscan_kswapd") {
        stat.pgscan_kswapd = value;
    } else if (key == "pgscan_direct") {
        stat.pgscan_direct = value;
    } else if (key == "pgsteal_kswapd") {
        stat.pgsteal_kswapd = value;
    } else if (key == "pgsteal_direct") {
        stat.pgsteal_direct = value;
    } else if (key == "pswpin") {
        stat.pswpin = value;
    } else if (key == "pswpout") {
        stat.pswpout = value;
    }
}

} // namespace

std::optional<VmStat> read_vmstat_file(const std::filesystem::path& path) {
    const auto lines = read_lines(path);

    if (lines.empty()) {
        return std::nullopt;
    }

    VmStat stat;

    for (const auto& line : lines) {
        std::istringstream stream(line);

        std::string key;
        std::uint64_t value = 0;

        stream >> key >> value;

        if (key.empty()) {
            continue;
        }

        assign_field(stat, key, value);
    }

    return stat;
}

} // namespace promon::linux_backend::procfs
