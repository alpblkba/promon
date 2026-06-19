#pragma once

#include "promon/core/types.hpp"

#include <vector>

namespace promon::linux_backend {

std::vector<ThreadInfo> read_threads(int pid);

} // namespace promon::linux_backend
