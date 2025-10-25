#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include "event.h"

#define STATES_LIST \
  X(STARTUP, 0) \
  X(IDLE, 1) \
  X(SEQUENCE_INPUT, 2) \
  X(SEQUENCE_PLAY, 100)

typedef enum {
#define X(id, value) id = value,
    STATES_LIST
#undef X
} FSM_state_t;

#endif

void FSM_Change_State(FSM_state_t new_state);
FSM_state_t FSM_Get_Current_State(void);

extern uint16_t FSM_timer;
extern event_t FSM_STATE_ENTER_EVENT;
extern event_t FSM_STATE_EXIT_EVENT;

// declare flag vars
/*#define X(id) extern unsigned char id##_flag; extern unsigned char id##_out;
STATES_LIST
#undef X*/
