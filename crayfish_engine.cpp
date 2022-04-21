#include "src/cegdk.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    ce::CEGDK cegdk{};

    try {
        cegdk.run();
    } catch(const std::exception &e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}