#ifndef ALARM_SET_HPP
#define ALARM_SET_HPP

#include "Event.hpp"

struct AlarmSet;


//creating Alarmset with fixed capacity and starting threshold
AlarmSet* alarm_create(int capacity, int threshold);


//frees memory used by Alarmset
void alarm_destroy(AlarmSet* alarms);

//return current temperature threshold
int alarm_getThreshold(const AlarmSet* alarms);

//updates temperature threshold
void alarm_setThreshold(AlarmSet* alarms, int threshold);

//return true if sensorId is currently in alarm state
bool alarm_contains(const AlarmSet* alarms, int sensorId);

//adds sensorID to alarm set if not currently active
bool alarm_add(AlarmSet* alarms, int sensorID);

//removes sensorId from alarm set if active
bool alarm_remove(AlarmSet* alarms, int sensorId);

//updates alarm set based on event
void alarm_updateFromEvent(AlarmSet* alarms, const Event& e);

//print all active alarms
void alarm_print(const AlarmSet* alarms);
    
#endif