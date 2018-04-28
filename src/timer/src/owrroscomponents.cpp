#include "timer/owrroscomponents.hpp"
#include "timer/timer.hpp"

void OwrRosComponents::registerTypes(const char *uri) {
    qmlRegisterType<Stopwatch>("bluesat.owr", 1, 0, "Stopwatch");
}

