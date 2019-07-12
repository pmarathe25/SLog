#include <SLog.hpp>

namespace Stealth::Log {
    Logger::Logger() : mCurrentLevel{Severity::INFO}, mMinLevel{Severity::INFO} {
        const char* minSev = std::getenv("SLOG_V");
        mMinLevel = minSev ? Severity{std::atoi(minSev)} : Severity::INFO;
    }

    Logger& Logger::severity(Severity level) {
        mCurrentLevel = level;
        return *this;
    }

    // For handling std::endl
    Logger& Logger::operator<<(std::ostream&(*f)(std::ostream&))
    {
        if (mCurrentLevel >= mMinLevel) {
            std::cout << f;
        }
        return *this;
    }

    Logger gLogger{};
} // Stealth::Log
