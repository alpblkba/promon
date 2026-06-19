#pragma once

#include "promon/core/types.hpp"

namespace promon {

VmStatRate compute_vmstat_rate(const VmStat& previous, const VmStat& current, double elapsed_seconds);

} // namespace promon
