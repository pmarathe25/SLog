#include "SLog/include/SLog.hpp"

#include <Stealth/STest.hpp>

STEST(FailInDebugBuild) {
    // Since assertions are only enabled in debug builds, this will be a no-op in other builds.
    S_ASSERT(false);
}

STEST_MAIN();
