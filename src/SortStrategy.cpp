#include "SortStrategy.hpp"
#include "Sort.hpp"

using namespace std;


//returns a sorting function based on the strategy name
SortFn getSortStrategy(const string& strategyName) {
    if (strategyName == "insertion" || strategyName.empty()) {
        return insertionSortByTimestamp;
    }
    return nullptr;
}


//sorts an event log using the specified sorting strategy
bool sortLogWithStrategy(EventLog* log, const string& strategyName) {
    if (log == nullptr) {
        return false;
    }

    SortFn sorter = getSortStrategy(strategyName);

    if (sorter == nullptr) {
        return false;
    }

    sorter(log);
    return true;
}