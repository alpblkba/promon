#pragma once

#include "promon/ui/renderer.hpp"

namespace promon::ui::cli {

class CliRenderer final : public Renderer {
public:
    void render(const Snapshot& snapshot) override;
};

} // namespace promon::ui::cli
