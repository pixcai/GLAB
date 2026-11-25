#include "engine.h"

#include <cstdlib>
#include <exception>

#include <spdlog/spdlog.h>

#if defined(__APPLE__)
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
#else
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
#endif

int main() {
    spdlog::set_level(spdlog::level::trace);
    try {
        glab::Engine engine{"GLAB", WINDOW_WIDTH, WINDOW_HEIGHT};
        engine.Run();
    } catch (const std::exception& e) {
        spdlog::critical(e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
