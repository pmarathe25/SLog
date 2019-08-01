#ifndef S_LOG_HPP
#define S_LOG_HPP

#ifndef DISABLE_S_LOG_STREAM_OVERLOADS
#include <ostream>
#include <typeinfo>

template <typename T, typename O>
constexpr std::ostream& operator<<(std::ostream& os, const std::pair<T, O>& pair) {
    return os << "{" << pair.first << ", " << pair.second << "}";
}

std::ostream& operator<<(std::ostream& os, const std::type_info& info) {
    return os << info.name();
}

template <typename T,
    // Enable for all containers
    typename = std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>,
    // except strings
    std::enable_if_t<!std::is_same<T, std::string>::value, int> = 0>
constexpr std::ostream& operator<<(std::ostream& os, const T& container) {
    os << "{";
    bool firstElem = true;
    for (const auto& elem : container) {
        os << (firstElem ? "" : ", ") << elem;
        firstElem = false;
    }
    return os << "}";
}
#endif

// Logging is only enabled for debug builds by default.
#ifdef S_DEBUG
#define ENABLE_S_LOG
#endif

#ifdef S_DEBUG
#include <cassert>
#define S_ASSERT(STATEMENT) assert(STATEMENT)
#else
#define S_ASSERT(STATEMENT)
#endif

#ifdef ENABLE_S_LOG
#include <iostream>
#include <string>
#include <sstream>

namespace Stealth::Log {
    enum class Severity : int {
        VERBOSE = 0,
        DEBUG = 1,
        INFO = 2,
        WARNING = 3,
        ERROR = 4,
        CRITICAL = 5,
    };

    class Logger {
    public:
        Logger() {
            const char* minSev = std::getenv("S_LOG_V");
            mMinSeverity = minSev ? Severity{std::atoi(minSev)} : Severity::INFO;
        }

        constexpr void log(Severity severity, const std::string& message) const {
            if (severity >= mMinSeverity) {
                std::cout << message;
            }
        }
    private:
        Severity mMinSeverity;
    };

    const Logger gLogger{};
} // Stealth::Log

#define S_LOG_RAW(SEVERITY, MESSAGE) { \
    std::stringstream __slog_ss{}; \
    __slog_ss << MESSAGE; \
    Stealth::Log::gLogger.log(static_cast<Stealth::Log::Severity>(SEVERITY), __slog_ss.str()); \
}
#else
#define S_LOG_RAW(SEVERITY, MESSAGE)
#endif // #ifdef ENABLE_S_LOG

#define S_LOG(SEVERITY, MESSAGE) S_LOG_RAW(SEVERITY, "[" << __FILE__ << ":" << __LINE__ << "] " << MESSAGE)

#define S_LOG_VERBOSE(MESSAGE) S_LOG(Stealth::Log::Severity::VERBOSE, MESSAGE)
#define S_LOG_DEBUG(MESSAGE) S_LOG(Stealth::Log::Severity::DEBUG, MESSAGE)
#define S_LOG_INFO(MESSAGE) S_LOG(Stealth::Log::Severity::INFO, MESSAGE)
#define S_LOG_WARNING(MESSAGE) S_LOG(Stealth::Log::Severity::WARNING, MESSAGE)
#define S_LOG_ERROR(MESSAGE) S_LOG(Stealth::Log::Severity::ERROR, MESSAGE)
#define S_LOG_CRITICAL(MESSAGE) S_LOG(Stealth::Log::Severity::CRITICAL, MESSAGE)

#endif // include guard
