#include "skywalker_remote_comms.h"

SkywalkerRemoteComm::SkywalkerRemoteComm(State *state): _state(state) {
    this->_commTimer = new TimerMS(SKW_REMOTE_COMM_PERIOD_MS);
}


/**
 * @brief Initialize communication with the remote;
 */
bool SkywalkerRemoteComm::begin() {
    this->_toRemote.begin();
    this->_fromRemote.begin();

    return true;
}


/**
 * @brief handle loop iteration. Communicate with the remote if the timer is up.
 *        Cycle between data transmit and data receive.
 */
bool SkywalkerRemoteComm::loopTick() {
    if ( !(this->_commTimer->hasTicked()) ) return true;

    if ( isTxCycle ) {
        this->_toRemote.sendMessage();
    } else {
        this->_fromRemote.getMessage();
    }

    isTxCycle = !isTxCycle;

    return true;
}
