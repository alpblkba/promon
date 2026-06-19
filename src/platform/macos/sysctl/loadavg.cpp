#include "promon/platform/macos/sysctl/loadavg.hpp"

namespace promon::macos_backend::sysctl_reader {

std::optional<std::array<double, 3>> read_loadavg() {
    return std::nullopt;
}

} // namespace promon::macos_backend::sysctl_reader
