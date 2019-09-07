// Tests the various operator<< overloads provided by SLog.
#include "SLog/include/SLog.hpp"

#include <STest.hpp>
#include <sstream>
#include <utility>

class StreamFixture {
protected:
    std::stringstream ss{};
};

STEST_F(StreamFixture, TypeInfo) {
    int i{0};
    ss << typeid(i);
    EXPECT_EQ(ss.str(), typeid(i).name());
}

STEST_F(StreamFixture, PairSameTypes) {
    ss << std::make_pair(0, 1);
    EXPECT_EQ(ss.str(), "{0, 1}");
}

STEST_F(StreamFixture, PairDifferentTypes) {
    ss << std::make_pair(0, 1.f);
    EXPECT_EQ(ss.str(), "{0, 1}");
}

STEST_MAIN();
