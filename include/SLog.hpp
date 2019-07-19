#ifndef SLOG_HPP
#define SLOG_HPP

#include <iostream>
#include <string>
#include <typeinfo>

#ifndef DISABLE_SLOG_STREAM_OVERLOADS
template <typename T, typename O>
constexpr std::ostream& operator<<(std::ostream& os, const std::pair<T, O>& pair) {
    return os << "{" << pair.first << ", " << pair.second << "}";
}

std::ostream& operator<<(std::ostream& os, const std::type_info& info);

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
        Logger();
        constexpr Logger& severity(Severity level) {
            mCurrentLevel = level;
            return *this;
        }

        // For handling std::endl
        constexpr Logger& operator<<(std::ostream&(*f)(std::ostream&))
        {
            if (mCurrentLevel >= mMinLevel) {
                std::cout << f;
            }
            return *this;
        }

        template <typename T>
        constexpr Logger& operator<<(T&& t)
        {
            if (mCurrentLevel >= mMinLevel) {
                std::cout << std::forward<T&&>(t);
            }
            return *this;
        }
    private:
        Severity mCurrentLevel, mMinLevel;
    };
    extern Logger gLogger;

    // Logs to oblivion
    class NullLogger {
    public:
        constexpr NullLogger& operator<<(std::ostream&(*f)(std::ostream&)) { return *this; }

        template <typename T>
        constexpr NullLogger& operator<<(T&& t) { return *this; }
    };

    namespace {
        NullLogger gNullLogger{};
    } // anonymous
} // Stealth::Log

// Logging is only enabled for debug builds by default.
#ifdef S_DEBUG
#define LOG_RAW(SEVERITY) Stealth::Log::gLogger.severity(static_cast<Stealth::Log::Severity>(SEVERITY))
#else
#define LOG_RAW(SEVERITY) Stealth::Log::gNullLogger
#endif

#define LOG(SEVERITY) LOG_RAW(SEVERITY) << "[" << __FILE__ << ":" << __LINE__ << "] "

#define LOG_VERBOSE() LOG(Stealth::Log::Severity::VERBOSE)
#define LOG_DEBUG() LOG(Stealth::Log::Severity::DEBUG)
#define LOG_INFO() LOG(Stealth::Log::Severity::INFO)
#define LOG_WARNING() LOG(Stealth::Log::Severity::WARNING)
#define LOG_ERROR() LOG(Stealth::Log::Severity::ERROR)
#define LOG_CRITICAL() LOG(Stealth::Log::Severity::CRITICAL)

#endif // include guard
