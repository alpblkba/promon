#pragma once

#include "promon/ui/render_model.hpp"

namespace promon::ui {

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const RenderDocument& document, const RenderOptions& options) = 0;
};

} // namespace promon::ui
