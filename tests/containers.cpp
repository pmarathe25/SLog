// Test various containers in the standard library.
#include "SLog/include/SLog.hpp"

#include <STest.hpp>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

class StreamFixture {
protected:
    std::stringstream ss{};
};

STEST_F(StreamFixture, VectorLog) {
    std::vector<int> test{0, 1, 2, 3, 4};
    ss << test;
    EXPECT_EQ(ss.str(), "{0, 1, 2, 3, 4}");
}

STEST_F(StreamFixture, MapLog) {
    std::map<int, int> test{
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4}};
    ss << test;
    EXPECT_EQ(ss.str(), "{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}}");
}

STEST_MAIN();
