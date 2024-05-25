#include "handler_chan.h"
#include "state.h"

#define CMD_CHAN "CHAN"


/*
 * Global state
 */
extern t_State state;

cmndChan cmnd_handler_chan;

// ----------------------------
cmndChan::cmndChan() :
    CmndBase ( CMD_CHAN ) {
}

bool cmndChan::doCommand(CmndParser *pars)
{
    if( strcmp( keyword, pars->cmndName() ) == 0 ) {
        char str[2];
        uint8_t n;
        uint8_t len = strlen( pars->paramStr(1) );
        if( len == TEMPERATURE_CHANNELS_MAX ) { // must match number of channels or take no action
            for( int i = 0; i < len; i++ ) {
                str[0] = pars->paramStr(1)[i]; // next character
                str[1] = '\0'; // force it to be char[2]
                n = atoi( str );
                if( n <= TEMPERATURE_CHANNELS_MAX ) {
                    state.cfg.chanMapping[i] = n;
                } else {
                    state.cfg.chanMapping[i] = 0;
                }
          }
          Serial.print(F("# Active channels set to "));
          Serial.println( pars->paramStr(1) );
        }
        return true;
    }

   return false;
}