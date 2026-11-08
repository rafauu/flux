#include <cstdlib>

import std;
import App;
import Logger;

int main()
{
    try
    {
        Logger::Guard _{};

        App app{};
        app.run();
    }
    catch (const std::exception& ex)
    {
        Logger::error("Fatal error: {}", ex.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
