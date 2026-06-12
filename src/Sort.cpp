#include "EventSort.hpp"

void insertionSortByTimestamp(EventLog* log) {
    if (log == nullptr) {
        return;
    }


int size = log_size(log);

if (size <= 1) {
    return;
}

for (int i = 1; i < size; i++) {
    Event key = log_get(log, i);
    int j = i -1;

    while (j >= 0 && log_get(log, j).timestamp > key.timestamp) {
        Event previous = log_get(log, j);
        log_set(log, j + 1, previous);
        j--;

    }

    log_set(log, j + 1, key);
}

}

bool isSortedByTimestamp(const EventLog* log){
    if (log == nullptr) {
        return true;
    }

    int size = log_size(log);

    if (size <= 1){
        return true;
    }

    for (int i = 0; i < size - 1; i++) {
        Event current = log_gett(log, i);
        Event next = log_get(log, i + 1);

        if (current.timestamp > next.timestamp) {
            return false;
        }
    }

    return true;
}