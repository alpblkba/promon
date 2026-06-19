#pragma once

#include <optional>
#include <string>

namespace promon::macos_backend::sysctl_reader {

std::optional<std::string> read_process_command_line(int pid);

} // namespace promon::macos_backend::sysctl_reader
