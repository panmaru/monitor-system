#include "collector/collector_interface.h"

namespace monitor {

CollectorInterface::~CollectorInterface() { stop(); }

void CollectorInterface::stop() {}

} // namespace monitor
