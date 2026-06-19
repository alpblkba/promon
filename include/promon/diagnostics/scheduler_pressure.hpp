#pragma once

#include "promon/core/snapshot.hpp"

#include <string>
#include <vector>

namespace promon::diagnostics {

std::vector<std::string> analyze_scheduler_pressure(const Snapshot& current);

} // namespace promon::diagnostics
