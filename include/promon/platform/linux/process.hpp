#pragma once

#include "promon/core/types.hpp"

#include <optional>
#include <vector>

namespace promon::linux_backend {

std::optional<ProcessInfo> read_process(int pid);
std::vector<ProcessInfo> read_processes();

} // namespace promon::linux_backend
