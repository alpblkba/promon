#pragma once

#include "promon/core/snapshot.hpp"

namespace promon::ui {

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const Snapshot& snapshot) = 0;
};

} // namespace promon::ui
