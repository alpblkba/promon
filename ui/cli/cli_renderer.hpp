#pragma once

#include "promon/ui/renderer.hpp"

namespace promon::ui::cli {

class CliRenderer final : public Renderer {
public:
    void render(const RenderDocument& document, const RenderOptions& options) override;
};

} // namespace promon::ui::cli
