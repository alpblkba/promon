#include "cli_renderer.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace promon::ui::cli {

namespace {

constexpr const char* reset = "\033[0m";
constexpr const char* bold = "\033[1m";
constexpr const char* dim = "\033[2m";
constexpr const char* cyan = "\033[36m";
constexpr const char* green = "\033[32m";
constexpr const char* yellow = "\033[33m";

std::string colorize(const char* color, const std::string& text, const RenderOptions& options) {
    if (!options.color) {
        return text;
    }

    return std::string(color) + text + reset;
}

std::size_t cell_width(const std::string& text) {
    return text.size();
}

std::string repeat(const std::string& text, std::size_t count) {
    std::string result;
    result.reserve(text.size() * count);

    for (std::size_t i = 0; i < count; ++i) {
        result += text;
    }

    return result;
}

std::vector<std::size_t> compute_widths(const RenderTable& table, const RenderOptions& options) {
    std::vector<std::size_t> widths(table.columns.size(), 0);

    for (std::size_t i = 0; i < table.columns.size(); ++i) {
        widths[i] = std::max(widths[i], cell_width(table.columns[i]));
    }

    for (const auto& row : table.rows) {
        const auto count = std::min(row.cells.size(), widths.size());

        for (std::size_t i = 0; i < count; ++i) {
            widths[i] = std::max(widths[i], cell_width(row.cells[i].display(options)));
        }
    }

    return widths;
}

void print_horizontal(const std::vector<std::size_t>& widths, const std::string& left, const std::string& middle, const std::string& right) {
    std::cout << left;

    for (std::size_t i = 0; i < widths.size(); ++i) {
        std::cout << repeat("─", widths[i] + 2);

        if (i + 1 < widths.size()) {
            std::cout << middle;
        }
    }

    std::cout << right << "\n";
}

void print_cells(const std::vector<std::string>& cells, const std::vector<std::size_t>& widths) {
    std::cout << "│";

    for (std::size_t i = 0; i < widths.size(); ++i) {
        const std::string value = i < cells.size() ? cells[i] : "";
        std::cout << " " << std::left << std::setw(static_cast<int>(widths[i])) << value << " │";
    }

    std::cout << "\n";
}

void print_header(const RenderDocument& document, const RenderOptions& options) {
    const std::string title = " " + document.title + " ";
    const std::size_t width = std::max<std::size_t>(title.size(), 60);

    if (options.color) {
        std::cout << bold << cyan;
    }

    std::cout << "┌" << repeat("─", width) << "┐\n";
    std::cout << "│" << std::left << std::setw(static_cast<int>(width)) << title << "│\n";
    std::cout << "└" << repeat("─", width) << "┘\n";

    if (options.color) {
        std::cout << reset;
    }

    std::cout << "\n";
}

void render_table(const RenderTable& table, const RenderOptions& options) {
    std::cout << colorize(bold, colorize(green, table.title, options), options) << "\n";

    const auto widths = compute_widths(table, options);

    print_horizontal(widths, "┌", "┬", "┐");
    print_cells(table.columns, widths);
    print_horizontal(widths, "├", "┼", "┤");

    for (const auto& row : table.rows) {
        std::vector<std::string> values;
        values.reserve(row.cells.size());

        for (const auto& cell : row.cells) {
            values.push_back(cell.display(options));
        }

        print_cells(values, widths);
    }

    print_horizontal(widths, "└", "┴", "┘");

    for (const auto& note : table.notes) {
        if (options.color) {
            std::cout << dim << yellow;
        }

        std::cout << "note: " << note << "\n";

        if (options.color) {
            std::cout << reset;
        }
    }

    std::cout << "\n";
}

} // namespace

void CliRenderer::render(const RenderDocument& document, const RenderOptions& options) {
    print_header(document, options);

    for (const auto& table : document.tables) {
        render_table(table, options);
    }

    for (const auto& note : document.notes) {
        if (options.color) {
            std::cout << dim << yellow;
        }

        std::cout << "note: " << note << "\n";

        if (options.color) {
            std::cout << reset;
        }
    }
}

} // namespace promon::ui::cli
