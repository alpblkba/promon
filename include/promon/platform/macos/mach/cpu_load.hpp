#pragma once

#include "promon/core/types.hpp"

#include <optional>

namespace promon::macos_backend::mach {

std::optional<CpuStat> read_cpu_load();

} // namespace promon::macos_backend::mach
