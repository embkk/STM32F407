#ifndef OBSERVER_H
#include "event.h"
#include <stdio.h>
#include "log.h"

void Event_Invoke(event_t e) {
  //log_message("Event %p invoked", e);
  callback_t callback;
  for(int i=0; i<CALLBACK_COUNT_LIMIT; i++) {
    callback = e[i];
    
    if(callback != NULL) {
      callback();
      //log_message("Event %p invoked, callback %p", e, callback);
    }
  }
}

void Event_AddListener(event_t e, callback_t callback) {
  for(int i=0; i<CALLBACK_COUNT_LIMIT; i++) {
    if(e[i]==NULL) {
      //log_message("Event %p add listener %p", e, callback);
      e[i] = callback;
      return;
    }
  }
}

void Event_RemoveListener(event_t e, callback_t callback) {
    for(int i=0; i<256; i++) {
      if(e[i]==callback) {
        e[i] = NULL;
        return;
      }
    }  
}

#endif