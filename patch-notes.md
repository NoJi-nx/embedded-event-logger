# Patch Notes


## Task 2 ADT: EventLog (dynamic list/array)

### 2.2 Create Eventlog source file

```cpp

struct EventLog {
    Event* events;
    int size;
    int capacity;

};

Eventlog* log_create(int capacity) {
    if (capacity <= 0) {
        capacity = 1;
    }
    
    EventLog* log = new EventLog;
    log->events = new Event[capacity];
    log->size = 0;
    log->capacity = capacity;

    return log;

}

void* log_destroy(EventLog* log) {
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

    if (log-<size == log->capacity) {
        int newCapacity = log->capacity * 2;
        Event* newEvents = new Event[newCapactiy];

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
```

### 2.1 Create Eventlog header

```cpp
#ifndef EVENT_LOG_HPP
#define EVENT_LOG_HPP

#include "Event.hpp"

using namespace std;

//ADT for storing events
//hidden struct
struct Eventlog;

//creates new EventLog with startpoint/capacity
EventLog* log_create(int capacity);

//frees all memory used by Eventlog
void log_destroy(EventLog* log);

//returns number of events now being stored
int log_size(const EventLog* log);

//adds new events to the log
void log_append(EventLog* log, Event e);

//gets events at index
Event log_get(const Eventlog* log, int index);


//replaces event at index
void log_set(EventLog* log, int index, Event e);

#endif

```
## Task 1: Event Model

### 1.1 Create the header file

```cpp
#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

using namespace std;

//enum för olika typer av event
enum EventType {
    TEMP,
    BUTTON,
    MOTION
};

// struct som lagrar event
struct Event {
    int timestamp;
    int sensorId;
    EventType type;
    int value;
};

//skapar en event och assignera nästa tidstämpel automatiskt
Event createEvent(int sensorId, EventType type, int value);

//konverterar enum till läsbar text
string eventTypeToString(EventType type);

#endif
```

### 1.2 Source File

```cpp
#include "Event.hpp"

using namespace std;

static int globalTimestamp = 0;

Event createEvent(int sensorId, EventType type, int value) {

    Event e;
    e.timestamp = globalTimestamp;
    e.sensorId = sensorId;
    e.type = type;
    e.value = value;

    globalTimestamp++;
    return e;

}

string eventTypeToString(EventType type) {
    switch(type) {
        case TEMP:
        return "TEMP";
        case BUTTON:
        return "BUTTON";
        case MOTION:
         return "MOTION";
         default:
         return "UNKNOWN";
    }
}
```

### 1.3 

```cpp
void printEvent(const Event& e) {
    cout  << "Timestamp: " << e.timestamp
          << ", Sensor ID: " << e.sensorId
          << ", Type: " << eventTypeToString(e.type)
          << ", Value: " << e.value
          << '\n';
}
int main() {
    Event e1 = createEvent(1, TEMP, 25);
    Event e2 = createEvent(2, BUTTON, 1);
    Event e3 = createEvent(3, MOTION, 100);

    printEvent(e1);
    printEvent(e2);
    printEvent(e3);

    return 0;

}
```