// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <fstream>
#include <string>

namespace spsdk {

enum LogLevel {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL,
};

class Logger {
public:
    Logger() : m_fn{} {}
    Logger(std::string const& pluginName, void (*fn)(char const*, ...));

    void logLnF(LogLevel level, char const* format, ...);

private:
    std::string m_pluginName;
    std::ofstream m_file;

    void (*m_fn)(char const*, ...);
};

extern Logger LOGGER;

} // namespace spsdk
