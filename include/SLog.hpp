#pragma once
#include <iostream>
#include <string>

#ifndef DISABLE_SLOG_STREAM_OVERLOADS
template <typename T, typename O>
std::ostream& operator<<(std::ostream& os, const std::pair<T, O>& pair) {
    return os << "{" << pair.first << ", " << pair.second << "}";
}

template <typename T,
    // Enable for all containers
    typename = std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>,
    // except strings
    std::enable_if_t<!std::is_same<T, std::string>::value, int> = 0>
std::ostream& operator<<(std::ostream& os, const T& container) {
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

    class Logger : public std::ostream {
    public:
        Logger() : mStream{&std::cout} {
            const char* minSev = std::getenv("SLOG_V");
            mMinLevel = minSev ? Severity{std::atoi(minSev)} : Severity::INFO;
        }

        void setStream(std::ostream& stream) { mStream = &stream; }
        std::ostream& getStream() { return *mStream; }

        Logger& severity(Severity level) { mCurrentLevel = level; return *this; }

        template <typename T>
        Logger& operator<<(T&& t)
        {
            if (mCurrentLevel >= mMinLevel) {
                this->getStream() << std::forward<T&&>(t);
            }
            return *this;
        }

        // For handling std::endl
        Logger& operator<<(std::ostream&(*f)(std::ostream&))
        {
            if (mCurrentLevel >= mMinLevel) {
                this->getStream() << f;
            }
            return *this;
        }
    private:
        std::ostream* mStream;
        Severity mCurrentLevel, mMinLevel;
    } static gLogger;
} // Stealth::Log

#define LOG(SEVERITY) Stealth::Log::gLogger.severity(static_cast<Stealth::Log::Severity>(SEVERITY)) << "[" << __FILE__ << ":" << __LINE__ << "] "

#define LOG_VERBOSE() LOG(Stealth::Log::Severity::VERBOSE)
#define LOG_DEBUG() LOG(Stealth::Log::Severity::DEBUG)
#define LOG_INFO() LOG(Stealth::Log::Severity::INFO)
#define LOG_WARNING() LOG(Stealth::Log::Severity::WARNING)
#define LOG_ERROR() LOG(Stealth::Log::Severity::ERROR)
#define LOG_CRITICAL() LOG(Stealth::Log::Severity::CRITICAL)
