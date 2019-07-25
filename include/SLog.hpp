#ifndef SLOG_HPP
#define SLOG_HPP

#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

#ifndef DISABLE_SLOG_STREAM_OVERLOADS
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
#define ENABLE_SLOG
#endif

#ifdef ENABLE_SLOG
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
            const char* minSev = std::getenv("SLOG_V");
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

#define LOG_RAW(SEVERITY, MESSAGE) { \
    std::stringstream __slog_ss{}; \
    __slog_ss << MESSAGE; \
    Stealth::Log::gLogger.log(static_cast<Stealth::Log::Severity>(SEVERITY), __slog_ss.str()); \
}
#else
#define LOG_RAW(SEVERITY, MESSAGE)
#endif // #ifdef S_DEBUG

#define LOG(SEVERITY, MESSAGE) LOG_RAW(SEVERITY, "[" << __FILE__ << ":" << __LINE__ << "] " << MESSAGE)

#define LOG_VERBOSE(MESSAGE) LOG(Stealth::Log::Severity::VERBOSE, MESSAGE)
#define LOG_DEBUG(MESSAGE) LOG(Stealth::Log::Severity::DEBUG, MESSAGE)
#define LOG_INFO(MESSAGE) LOG(Stealth::Log::Severity::INFO, MESSAGE)
#define LOG_WARNING(MESSAGE) LOG(Stealth::Log::Severity::WARNING, MESSAGE)
#define LOG_ERROR(MESSAGE) LOG(Stealth::Log::Severity::ERROR, MESSAGE)
#define LOG_CRITICAL(MESSAGE) LOG(Stealth::Log::Severity::CRITICAL, MESSAGE)

#endif // include guard
