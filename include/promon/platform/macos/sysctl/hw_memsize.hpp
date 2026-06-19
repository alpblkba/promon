#pragma once

#include <cstdint>
#include <optional>

namespace promon::macos_backend::sysctl_reader {

std::optional<std::uint64_t> read_hw_memsize_bytes();

} // namespace promon::macos_backend::sysctl_reader
