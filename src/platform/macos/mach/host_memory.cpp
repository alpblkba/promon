#include "promon/platform/macos/mach/host_memory.hpp"

#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <mach/vm_statistics.h>

namespace promon::macos_backend::mach {

std::optional<HostMemory> read_host_memory() {
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    vm_statistics64_data_t stats{};

    const kern_return_t stat_result = host_statistics64(
        mach_host_self(),
        HOST_VM_INFO64,
        reinterpret_cast<host_info64_t>(&stats),
        &count
    );

    if (stat_result != KERN_SUCCESS) {
        return std::nullopt;
    }

    vm_size_t page_size = 0;
    const kern_return_t page_result = host_page_size(mach_host_self(), &page_size);

    if (page_result != KERN_SUCCESS) {
        return std::nullopt;
    }

    HostMemory memory;
    memory.page_size = static_cast<std::uint64_t>(page_size);

    memory.free_pages = stats.free_count;
    memory.active_pages = stats.active_count;
    memory.inactive_pages = stats.inactive_count;
    memory.wired_pages = stats.wire_count;
    memory.speculative_pages = stats.speculative_count;
    memory.compressor_pages = stats.compressor_page_count;

    memory.faults = stats.faults;
    memory.cow_faults = stats.cow_faults;
    memory.pageins = stats.pageins;
    memory.pageouts = stats.pageouts;
    memory.zero_fill_count = stats.zero_fill_count;
    memory.reactivations = stats.reactivations;
    memory.purges = stats.purges;

    return memory;
}

} // namespace promon::macos_backend::mach
