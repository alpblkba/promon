#include "promon/platform/macos/sysctl/hw_memsize.hpp"

#include <sys/sysctl.h>

namespace promon::macos_backend::sysctl_reader {

std::optional<std::uint64_t> read_hw_memsize_bytes() {
    std::uint64_t value = 0;
    std::size_t size = sizeof(value);

    if (sysctlbyname("hw.memsize", &value, &size, nullptr, 0) != 0) {
        return std::nullopt;
    }

    return value;
}

} // namespace promon::macos_backend::sysctl_reader
