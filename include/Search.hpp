#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "EventLog.hpp"

//searching the log linear for events with sensorId
int findEventsBySensorId(const EventLog* log, int sensorId);

#endif