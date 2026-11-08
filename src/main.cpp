#include <cstdlib>

import std;
import App.Application;
import Core.Logger;

namespace logger = core::logger;

int main()
{
    logger::Guard _{};

    try
    {
        app::Application{}.run();
    }
    catch (const std::exception& ex)
    {
        logger::error("Fatal error: {}", ex.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
