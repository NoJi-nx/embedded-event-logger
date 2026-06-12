#ifndef EVENT_SORT_HPP
#define EVENT_SORT_HPP

#include "EventLog.hpp"

//sorting the log by timestamp using insertion
void insertionSortByTimestamp(EventLog* log);

//check if log is sorted by timestamp
bool isSortedByTimestamp(const EventLog* log);

#endif