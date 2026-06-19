#include "promon/platform/macos/libproc/process_io.hpp"

namespace promon::macos_backend::libproc_reader {

std::optional<ProcessIoRaw> read_process_io(int) {
    return std::nullopt;
}

} // namespace promon::macos_backend::libproc_reader
