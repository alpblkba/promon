#pragma once

#include "promon/core/types.hpp"

#include <vector>

namespace promon::macos_backend {

std::vector<ThreadInfo> read_threads(int pid);

} // namespace promon::macos_backend
