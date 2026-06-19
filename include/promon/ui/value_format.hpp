#pragma once

#include "promon/ui/render_model.hpp"

#include <cstdint>
#include <string>

namespace promon::ui {

RenderCell format_kib(std::uint64_t kib);
RenderCell format_counter(std::uint64_t value);
RenderCell format_rate(double value_per_second);
RenderCell format_plain(std::string value);

} // namespace promon::ui
