#ifndef sensor_h
#define sensor_h

using namespace QP;

uint32_t const BSP_TICKS_PER_SEC = static_cast<uint32_t>(100);

enum SensorSignals {
    DUMMY_SIG = Q_USER_SIG,
    MAX_PUB_SIG,  // the last published signal

    TIMEOUT_SIG,
    MAX_SIG       // the last signal
};

extern QActive * const AO_Sensor; // opaque pointer

#endif // blinky_h
