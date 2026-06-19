#pragma once

#include "promon/app/options.hpp"

namespace promon::app {

class Application {
public:
    explicit Application(Options options);

    int run();

private:
    Options options_;
};

} // namespace promon::app
