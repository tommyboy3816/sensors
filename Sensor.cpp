#include "qpcpp.h"
//#include "bsp.h"
#include "Sensor.h"

//Q_DEFINE_THIS_FILE

//............................................................................
class Sensor : public QActive {
private:
    QTimeEvt m_timeEvt;

public:
    Sensor();

protected:
    static QState initial(Sensor * const me, QEvt const * const e);
    static QState off(Sensor * const me, QEvt const * const e);
    static QState on(Sensor * const me, QEvt const * const e);
};

// local bjects --------------------------------------------------------------
Sensor l_sensor;

// global objects ------------------------------------------------------------
QActive * const AO_Sensor = &l_sensor; // opaque pointer

//............................................................................
Sensor::Sensor()
  : QActive(Q_STATE_CAST(&Sensor::initial)),
    m_timeEvt(this, TIMEOUT_SIG, 0U)
{
    // empty
}

// HSM definition ------------------------------------------------------------
QState Sensor::initial(Sensor * const me, QEvt const * const e) {
    (void)e; // unused parameter

    // arm the time event to expire in half a second and every half second
    me->m_timeEvt.armX(BSP_TICKS_PER_SEC/2U, BSP_TICKS_PER_SEC/2U);
    return Q_TRAN(&Sensor::off);
}
//............................................................................
QState Sensor::off(Sensor * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            //BSP_ledOff();
            status = Q_HANDLED();
            break;
        }
        case TIMEOUT_SIG: {
            status = Q_TRAN(&Sensor::on);
            break;
        }
        default: {
            status = Q_SUPER(&QHsm::top);
            break;
        }
    }
    return status;
}
//............................................................................
QState Sensor::on(Sensor * const me, QEvt const * const e) {
    QState status;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            //BSP_ledOn();
            status = Q_HANDLED();
            break;
        }
        case TIMEOUT_SIG: {
            status = Q_TRAN(&Sensor::off);
            break;
        }
        default: {
            status = Q_SUPER(&QHsm::top);
            break;
        }
    }
    return status;
}
