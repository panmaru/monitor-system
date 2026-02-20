#include "utils/host.h"

namespace monitor {

std::ostream &operator<<(std::ostream &os, const Host &host) {
    return os << host.toString();
}

} // namespace monitor