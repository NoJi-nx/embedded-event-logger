#ifndef SORT_STRATEGY_HPP
#define SORT_STRATEGY_HPP

#include "EventLog.hpp"
#include <string>

using namespace std;

//function pointer type for sorting strategies
using SortFn = void (*)(EventLog* log);

//return a sorting function based on the strategy name
SortFn getSortStrategy(const string& strategyName);

//runs selected sorting strategy
bool sortLogWithStrategy(EventLog* log, const string& strategyName);

#endif