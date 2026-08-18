#ifndef SORT_HPP
#define SORT_HPP

#include "EventLog.hpp"

//sorting the log by timestamp using insertion
void insertionSortByTimestamp(EventLog* log);

//sorting the log by timestamp using selection
void selectionSortByTimestamp(EventLog* log);

//check if log is sorted by timestamp
bool isSortedByTimestamp(const EventLog* log);

#endif