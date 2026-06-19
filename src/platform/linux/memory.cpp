#include "promon/platform/linux/memory.hpp"

#include "promon/platform/linux/procfs/meminfo.hpp"

namespace promon::linux_backend {

SystemMemory read_system_memory() {
    SystemMemory memory;

    const auto meminfo = procfs::read_meminfo();

    if (!meminfo) {
        return memory;
    }

    memory.total_kb = meminfo->mem_total_kb;
    memory.available_kb = meminfo->mem_available_kb;
    memory.free_kb = meminfo->mem_free_kb;
    memory.cached_kb = meminfo->cached_kb;
    memory.buffers_kb = meminfo->buffers_kb;
    memory.swap_total_kb = meminfo->swap_total_kb;
    memory.swap_free_kb = meminfo->swap_free_kb;

    return memory;
}

} // namespace promon::linux_backend
