#include "promon/platform/macos/libproc/process_info.hpp"

namespace promon::macos_backend::libproc_reader {

std::optional<ProcessInfoRaw> read_process_info(int) {
    return std::nullopt;
}

} // namespace promon::macos_backend::libproc_reader
