#pragma once

#include <spdlog/spdlog.h>

#if defined(NDEBUG)
#    define GLAB_INIT_LOGGER() spdlog::set_level(spdlog::level::info)
#else
#    define GLAB_INIT_LOGGER() spdlog::set_level(spdlog::level::debug)
#endif

#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
