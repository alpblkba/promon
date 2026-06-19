#pragma once

#include <optional>

namespace promon::macos_backend::sysctl_reader {

std::optional<double> read_uptime_seconds();

} // namespace promon::macos_backend::sysctl_reader
