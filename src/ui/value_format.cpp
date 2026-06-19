#include "promon/ui/value_format.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

namespace promon::ui {

namespace {

std::string fixed2(double value) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
}

std::string to_string_u64(std::uint64_t value) {
    return std::to_string(value);
}

} // namespace

RenderCell format_kib(std::uint64_t kib) {
    const double gib = static_cast<double>(kib) / 1024.0 / 1024.0;
    return RenderCell(fixed2(gib) + " GiB", to_string_u64(kib) + " KiB");
}

RenderCell format_counter(std::uint64_t value) {
    const double v = static_cast<double>(value);

    if (value >= 1'000'000'000'000ULL) {
        return RenderCell(fixed2(v / 1'000'000'000'000.0) + "T", to_string_u64(value));
    }

    if (value >= 1'000'000'000ULL) {
        return RenderCell(fixed2(v / 1'000'000'000.0) + "B", to_string_u64(value));
    }

    if (value >= 1'000'000ULL) {
        return RenderCell(fixed2(v / 1'000'000.0) + "M", to_string_u64(value));
    }

    if (value >= 1'000ULL) {
        return RenderCell(fixed2(v / 1'000.0) + "K", to_string_u64(value));
    }

    return RenderCell(to_string_u64(value), to_string_u64(value));
}

RenderCell format_rate(double value_per_second) {
    const double abs_value = value_per_second < 0.0 ? -value_per_second : value_per_second;

    std::string human;

    if (abs_value >= 1'000'000'000.0) {
        human = fixed2(value_per_second / 1'000'000'000.0) + "B/s";
    } else if (abs_value >= 1'000'000.0) {
        human = fixed2(value_per_second / 1'000'000.0) + "M/s";
    } else if (abs_value >= 1'000.0) {
        human = fixed2(value_per_second / 1'000.0) + "K/s";
    } else {
        human = fixed2(value_per_second) + "/s";
    }

    return RenderCell(human, fixed2(value_per_second) + "/s");
}

RenderCell format_plain(std::string value) {
    return RenderCell(std::move(value));
}

} // namespace promon::ui
