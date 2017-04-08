#include "timer/owrroscomponents.hpp"
#include "timer/timer.hpp"

void OwrRosComponents::registerTypes(const char *uri) {
    qmlRegisterType<Timer>("bluesat.owr", 1, 0, "Timer");
}

