module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

module Core.Logger;

import std;

namespace core::logger
{
    void init()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logger = std::make_shared<spdlog::logger>("flux", spdlog::sinks_init_list{console_sink});
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] %^[%-7l] [%-18s:%4#] %v%$");
    }

    void shutdown()
    {
        spdlog::shutdown();
    }

    void logMessage(std::source_location loc, int level, std::string_view msg)
    {
        spdlog::default_logger_raw()->log(
            spdlog::source_loc{loc.file_name(), static_cast<int>(loc.line()), loc.function_name()},
            spdlog::level::level_enum{level},
            "{}",
            msg
        );
    }
}
