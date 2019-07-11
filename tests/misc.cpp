// Tests the various operator<< overloads provided by SLog.
#include <Stealth/STest.hpp>
#include <sstream>
#include <utility>

#include "SLog.hpp"

class StreamFixture {
protected:
    std::stringstream ss{};
};

STEST_F(StreamFixture, PairSameTypes) {
    ss << std::make_pair(0, 1);
    EXPECT_EQ(ss.str(), "{0, 1}");
}

STEST_F(StreamFixture, PairDifferentTypes) {
    ss << std::make_pair(0, 1.f);
    EXPECT_EQ(ss.str(), "{0, 1}");
}

int main(int argc, const char* argv[]) {
    return static_cast<int>(RUN_STESTS(argc, argv));
}
