#ifndef EVENT_LOOP_HPP
#define EVENT_LOOP_HPP

#include "EventLog.hpp"
#include "EventQueue.hpp"
#include "AlarmSet.hpp"
#include "LatestEventStore.hpp"

//creating a simulated event
Event produceEvent();


/* runs all these events: 
1 produce event
2. enqueue event
3. dequeue event
4. append event to log
5. update alarms
*/
void eventLoop_tick(Queue* queue, EventLog* log, AlarmSet* alarms, LatestEventStore* latestStore);

//runs multple event loop 
void eventLoop_runTicks(Queue* queue, EventLog* log, AlarmSet* alarms, LatestEventStore* latestStore, int iterations);

#endif