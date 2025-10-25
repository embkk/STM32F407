#ifndef EVENT_H
#define EVENT_H

#define CALLBACK_COUNT_LIMIT 32

typedef void(*callback_t)(void);
typedef callback_t event_t[CALLBACK_COUNT_LIMIT];

void Event_Invoke(event_t);
void Event_AddListener(event_t, callback_t);
void Event_RemoveListener(event_t, callback_t);

#endif