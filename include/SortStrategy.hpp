#ifndef SORT_STRATEGY_HPP
#define SORT_STRATEGY_HPP

#include "EventLog.hpp"
#include <string>

//function pointer type for sorting strategies
using namespace std;

//return a sorting function based on the strategy name
using SortFn = void (*)(EventLog* log);

//runs selected sorting strategy
SortFn getSortStrategy(const string& strategyName);


#endif