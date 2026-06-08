# Patch Notes

## Task 3 ADT: EventQueue (ring buffer)

### 3.1 Create EventQueue header

```cpp
#ifndef EVENT_QUEUE_HPP
#define EVENY_QUEUE_HPP

#include "Event.hpp"

//ADT for incoming events
struct Queue;

//create a queue with fixed capacity
Queue* queue_create(int capacity);

//free all memory used by the queue
void queue_destroy(Queue* q);

//return true if queue is has no events
bool queue_isEmpty(const Queue* q);

//return true if queue is full
bool queue_isFull(const Queue* q);

//adds an event to the queue
bool queue_enqueue(Queue* q, Event e);

//removes the oldest event from queue
bool queue_dequeue(Queue* q, Event* out);

#endif

```


## Task 2 ADT: EventLog (dynamic list/array)

### 2.3 Test in main.cpp

```cpp
void printEvent(const Event& e) {
    cout  << "Timestamp: " << e.timestamp
          << ", Sensor ID: " << e.sensorId
          << ", Type: " << eventTypeToString(e.type)
          << ", Value: " << e.value
          << '\n';
}

void printLog(const EventLog* log) {
    int size = log_size(log);

    if (size == 0) {
        cout << "Log is empty.\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        Event e = log_get(log, i);
        printEvent(e);
    }
}
int main() {
    EventLog* log = log_create(2);

    cout <<"Log size: " << log_size(log) << '\n';

    Event e1 = createEvent(1, TEMP, 15);
    Event e2 = createEvent(2, BUTTON, 1);
    Event e3 = createEvent(3, MOTION, 100);

    log_append(log, e1);
    log_append(log, e2);
    log_append(log, e3);

    cout << "Log size after append: " << log_size(log) << '\n';

    cout << "\nTesting log_get index 1:\n";
    Event selected = log_get(log, 1);
    printEvent(selected);

    cout << "\nTesting log_get index 1:\n";
    Event replacement = createEvent(9, TEMP, 99);
    log_set(log, 1, replacement);

    printLog(log);

    cout << "\nTesting invalid index:\n";
    log_get(log, 99);

    log_destroy(log);

    return 0;

}


```

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