#include "SLog/include/SLog.hpp"

namespace Stealth::Log {
    Logger::Logger() : mCurrentLevel{Severity::INFO}, mMinLevel{Severity::INFO} {
        const char* minSev = std::getenv("SLOG_V");
        mMinLevel = minSev ? Severity{std::atoi(minSev)} : Severity::INFO;
    }

    Logger gLogger{};
} // Stealth::Log
