// Tests the various operator<< overloads provided by SLog.
#include <Stealth/STest.hpp>
#include <sstream>
#include <utility>

#include "SLog.hpp"

STEST(PairSameTypes) {
    std::stringstream ss{};
    ss << std::make_pair(0, 1);
    EXPECT_EQ(ss.str(), "{0, 1}");
}