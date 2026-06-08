#include "EventLog.hpp"
#include <iostream>

using namespace std;

struct EventLog {
    Event* events;
    int size;
    int capacity;

};

EventLog* log_create(int capacity) {
    if (capacity <= 0) {
        capacity = 1;
    }
    
    EventLog* log = new EventLog;
    log->events = new Event[capacity];
    log->size = 0;
    log->capacity = capacity;

    return log;

}

void log_destroy(EventLog* log) {
    if (log == nullptr) {
        return;
    }

    delete[] log->events;
    delete log;
}

int log_size(const EventLog* log) {
    if (log == nullptr) {
        return 0;
    }

    return log->size;
}

void log_append(EventLog* log, Event e) {
    if (log ==nullptr) {
        return;
    }

    if (log->size == log->capacity) {
        int newCapacity = log->capacity * 2;
        Event* newEvents = new Event[newCapacity];

        for (int i = 0; i < log->size; i++) {
            newEvents[i] = log->events [i];
        }

        delete[] log->events;

        log->events = newEvents;
        log->capacity = newCapacity;
    }

    log->events[log->size] = e;
    log->size++;
}

Event log_get(const EventLog* log, int index) {
    if (log == nullptr || index < 0 || index >= log->size) {
        cout << "Wrong log index.\n";
        return Event{-1, -1, TEMP, 0};
    }

    return log->events[index];
}

void log_set(EventLog* log, int index, Event e) {
    if (log == nullptr || index < 0 || index >= log->size) {
        cout << "Wrong log index.\n";
        return;
    }

    log->events[index] = e;
}