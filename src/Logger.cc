// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <spsdk/Logger.hh>

using namespace spsdk;

Logger spsdk::logger;

Logger::Logger(std::string const& pluginName, void (*fn)(char const*, ...))
    : m_pluginName(pluginName)
    , m_fn(fn)
{
    char filepath[128];
    snprintf(filepath, 128, "logs/%s.txt", pluginName.c_str());

    if (!std::filesystem::exists("logs"))
        std::filesystem::create_directory("logs");

    m_file.open(filepath, std::ios::app);

    if (!m_file.is_open())
        logLnF(LOG_LEVEL_ERROR, "File could not be opened '%s'", filepath);
}

void Logger::logLnF(LogLevel level, char const* format, ...) {
    va_list args;
    va_start(args, format);

    char text[512];
    vsnprintf(text, 512, format, args);

    va_end(args);

    static char const* LEVELS_NAME[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
        "CRITICAL",
    };

    if (m_file.is_open())
        m_file << '[' << LEVELS_NAME[level] << "]: " << text << std::endl;

    m_fn("[%s | %s]: %s", LEVELS_NAME[level], m_pluginName.c_str(), text);

    if (level == LOG_LEVEL_CRITICAL)
        abort();
}
