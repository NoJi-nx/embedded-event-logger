#ifndef EVENT_LOOP_HPP
#define EVENT_LOOP_HPP

#include "EventLog.hpp"
#include "EventQueue.hpp"

//creating a simulated event
Event produceEvent();


//runs all these events: 1 produce event, enqueue event, dequee event, append event to log
void eventLoop_tick(Queue* queue, EventLog* log);

//runs multple event loop 
void eventLoop_runTicks(Queue* queue, EventLog* log, int iterations);

#endif