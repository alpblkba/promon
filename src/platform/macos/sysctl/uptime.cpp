#include "promon/platform/macos/sysctl/uptime.hpp"

namespace promon::macos_backend::sysctl_reader {

std::optional<double> read_uptime_seconds() {
    return std::nullopt;
}

} // namespace promon::macos_backend::sysctl_reader
