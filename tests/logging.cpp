#include "SLog/include/SLog.hpp"

#include <Stealth/STest.hpp>
#include <iostream>

STEST(LoggingInfoDefaultSeverity) {
    LOG_INFO("This is a test logging message" << std::endl);
}

STEST(LoggingSuppressedByDefault) {
    LOG_DEBUG("This is a test logging message that SHOULD NOT DISPLAY" << std::endl);
}

int main(int argc, const char* argv[]) {
    return static_cast<int>(RUN_STESTS(argc, argv));
}
