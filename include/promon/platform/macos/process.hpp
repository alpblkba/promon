#pragma once

#include "promon/core/types.hpp"

#include <vector>

namespace promon::macos_backend {

std::vector<ProcessInfo> read_processes();

} // namespace promon::macos_backend
