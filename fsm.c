#include "fsm.h"
#include "log.h"
#include "buttons.h"

// declare flag vars
/*#define X(id) unsigned char id##_flag; unsigned char id##_out;
STATES_LIST
#undef X*/

uint16_t FSM_timer;
FSM_state_t FSM_state;
event_t FSM_STATE_EXIT_EVENT;
event_t FSM_STATE_ENTER_EVENT;

void FSM_Change_State(FSM_state_t new_state) {
  Event_Invoke(FSM_STATE_EXIT_EVENT);
  LOG_MESSAGE("FSM change state from #%d to #%d (>=%d ms)", new_state, FSM_state, FSM_timer);
  FSM_timer = 0;
  FSM_state = new_state;
  Event_Invoke(FSM_STATE_ENTER_EVENT);
}

FSM_state_t FSM_Get_Current_State(void) {
  return FSM_state;
}