#include <Stealth/STest.hpp>
#include <iostream>

#include "SLog.hpp"

STEST(LoggingInfoDefaultSeverity) {
    LOG_INFO() << "This is a test logging message" << std::endl;
}

STEST(LoggingSuppressedByDefault) {
    LOG_DEBUG() << "This is a test logging message that SHOULD NOT DISPLAY" << std::endl;
}
