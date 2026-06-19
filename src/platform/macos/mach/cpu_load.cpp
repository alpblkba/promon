#include "promon/platform/macos/mach/cpu_load.hpp"

namespace promon::macos_backend::mach {

std::optional<CpuStat> read_cpu_load() {
    return std::nullopt;
}

} // namespace promon::macos_backend::mach
