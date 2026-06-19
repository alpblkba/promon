#pragma once

#include "promon/core/snapshot.hpp"

#include <string>
#include <vector>

namespace promon::diagnostics {

std::vector<std::string> analyze_io_pressure(const Snapshot& current);

} // namespace promon::diagnostics
