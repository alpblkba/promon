#include "promon/ui/snapshot_presenter.hpp"

#include "promon/ui/value_format.hpp"

namespace promon::ui {

namespace {

RenderTable present_memory(const SystemMemory& memory) {
    const auto used_kb =
        memory.total_kb > memory.available_kb
            ? memory.total_kb - memory.available_kb
            : 0;

    RenderTable table;
    table.title = "memory";
    table.columns = {"metric", "value"};

    table.rows.push_back({{format_plain("total"), format_kib(memory.total_kb)}});
    table.rows.push_back({{format_plain("used"), format_kib(used_kb)}});
    table.rows.push_back({{format_plain("available"), format_kib(memory.available_kb)}});
    table.rows.push_back({{format_plain("free"), format_kib(memory.free_kb)}});
    table.rows.push_back({{format_plain("cached"), format_kib(memory.cached_kb)}});

    return table;
}

RenderTable present_vmstat(const VmStat& vmstat) {
    RenderTable table;
    table.title = "virtual memory activity";
    table.columns = {"counter", "value"};

    table.rows.push_back({{format_plain("pgfault"), format_counter(vmstat.pgfault)}});
    table.rows.push_back({{format_plain("pgmajfault"), format_counter(vmstat.pgmajfault)}});
    table.rows.push_back({{format_plain("pgscan_kswapd"), format_counter(vmstat.pgscan_kswapd)}});
    table.rows.push_back({{format_plain("pgscan_direct"), format_counter(vmstat.pgscan_direct)}});
    table.rows.push_back({{format_plain("pgsteal_kswapd"), format_counter(vmstat.pgsteal_kswapd)}});
    table.rows.push_back({{format_plain("pgsteal_direct"), format_counter(vmstat.pgsteal_direct)}});
    table.rows.push_back({{format_plain("pswpin"), format_counter(vmstat.pswpin)}});
    table.rows.push_back({{format_plain("pswpout"), format_counter(vmstat.pswpout)}});

#if defined(__APPLE__)
    table.notes.push_back("macOS maps Mach VM counters into the shared VmStat model.");
    table.notes.push_back("pgmajfault is approximated using pageins; reclaim counters are Linux-only.");
#elif defined(__linux__)
    table.notes.push_back("vm counters are read from /proc/vmstat.");
    table.notes.push_back("counters are cumulative; rates will come in watch/delta mode.");
#endif

    return table;
}

RenderTable present_vmstat_rate(const VmStatRate& rate) {
    RenderTable table;
    table.title = "virtual memory rate";
    table.columns = {"signal", "rate"};

    table.rows.push_back({{format_plain("pgfault/s"), format_rate(rate.pgfault_per_sec)}});
    table.rows.push_back({{format_plain("pgmajfault/s"), format_rate(rate.pgmajfault_per_sec)}});
    table.rows.push_back({{format_plain("pgscan/s"), format_rate(rate.pgscan_per_sec)}});
    table.rows.push_back({{format_plain("pgscan_kswapd/s"), format_rate(rate.pgscan_kswapd_per_sec)}});
    table.rows.push_back({{format_plain("pgscan_direct/s"), format_rate(rate.pgscan_direct_per_sec)}});
    table.rows.push_back({{format_plain("pgsteal/s"), format_rate(rate.pgsteal_per_sec)}});
    table.rows.push_back({{format_plain("pgsteal_kswapd/s"), format_rate(rate.pgsteal_kswapd_per_sec)}});
    table.rows.push_back({{format_plain("pgsteal_direct/s"), format_rate(rate.pgsteal_direct_per_sec)}});
    table.rows.push_back({{format_plain("pswpin/s"), format_rate(rate.pswpin_per_sec)}});
    table.rows.push_back({{format_plain("pswpout/s"), format_rate(rate.pswpout_per_sec)}});

#if defined(__APPLE__)
    table.notes.push_back("macOS rate signals are derived from Mach VM counters.");
#elif defined(__linux__)
    table.notes.push_back("Linux rate signals are deltas from /proc/vmstat counters.");
#endif

    return table;
}

} // namespace

RenderDocument present_snapshot(const Snapshot& snapshot) {
    RenderDocument document;
    document.title = "promon v0 · tiny low-level process monitor";

    document.tables.push_back(present_memory(snapshot.memory));
    document.tables.push_back(present_vmstat(snapshot.vmstat));

    if (snapshot.vmstat_rate) {
        document.tables.push_back(present_vmstat_rate(*snapshot.vmstat_rate));
    }

    return document;
}

} // namespace promon::ui
