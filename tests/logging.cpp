#include "SLog/include/SLog.hpp"

#include <Stealth/STest.hpp>
#include <iostream>

STEST(LoggingInfoDefaultSeverity) {
    S_LOG_INFO("This is a test logging message" << std::endl);
}

STEST(LoggingSuppressedByDefault) {
    S_LOG_DEBUG("This is a test logging message that SHOULD NOT DISPLAY" << std::endl);
}

STEST_MAIN();
