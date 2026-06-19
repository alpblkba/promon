#pragma once

#include <string>
#include <vector>

namespace promon::ui {

struct RenderOptions {
    bool verbose = false;
    bool raw_values = false;
    bool color = true;
};

struct RenderCell {
    std::string human;
    std::string raw;

    RenderCell() = default;

    explicit RenderCell(std::string value)
        : human(std::move(value)), raw(human) {}

    RenderCell(std::string human_value, std::string raw_value)
        : human(std::move(human_value)), raw(std::move(raw_value)) {}

    std::string display(const RenderOptions& options) const {
        if (options.raw_values) {
            return raw.empty() ? human : raw;
        }

        if (options.verbose && !raw.empty() && raw != human) {
            return human + " (" + raw + ")";
        }

        return human;
    }
};

struct RenderRow {
    std::vector<RenderCell> cells;
};

struct RenderTable {
    std::string title;
    std::vector<std::string> columns;
    std::vector<RenderRow> rows;
    std::vector<std::string> notes;
};

struct RenderDocument {
    std::string title;
    std::vector<RenderTable> tables;
    std::vector<std::string> notes;
};

} // namespace promon::ui
