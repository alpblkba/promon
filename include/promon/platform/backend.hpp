#pragma once

#include "promon/core/snapshot.hpp"

namespace promon {

class Backend {
public:
    virtual ~Backend() = default;
    virtual Snapshot collect() = 0;
};

} // namespace promon
