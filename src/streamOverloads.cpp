#include "SLog/include/SLog.hpp"

std::ostream& operator<<(std::ostream& os, const std::type_info& info) {
    return os << info.name();
}
