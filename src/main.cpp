#include "promon/app/application.hpp"
#include "promon/app/options.hpp"

int main(int argc, char** argv) {
    const auto options = promon::app::parse_options(argc, argv);
    promon::app::Application application(options);
    return application.run();
}
