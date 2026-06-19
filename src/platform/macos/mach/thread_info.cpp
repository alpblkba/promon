#include "promon/platform/macos/mach/thread_info.hpp"

namespace promon::macos_backend::mach {

std::vector<ThreadInfo> read_threads(int) {
    return {};
}

} // namespace promon::macos_backend::mach
