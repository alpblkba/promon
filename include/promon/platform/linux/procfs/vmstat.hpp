#pragma once

#include "promon/core/types.hpp"

#include <filesystem>
#include <optional>

namespace promon::linux_backend::procfs {

std::optional<VmStat> read_vmstat_file(const std::filesystem::path& path = "/proc/vmstat");

} // namespace promon::linux_backend::procfs
