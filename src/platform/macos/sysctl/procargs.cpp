#include "promon/platform/macos/sysctl/procargs.hpp"

namespace promon::macos_backend::sysctl_reader {

std::optional<std::string> read_process_command_line(int) {
    return std::nullopt;
}

} // namespace promon::macos_backend::sysctl_reader
