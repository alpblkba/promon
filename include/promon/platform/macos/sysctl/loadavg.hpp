#pragma once

#include <array>
#include <optional>

namespace promon::macos_backend::sysctl_reader {

std::optional<std::array<double, 3>> read_loadavg();

} // namespace promon::macos_backend::sysctl_reader
