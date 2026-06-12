# Patch Notes

## Task 5 Sorting (1 algorithm)

### 5.1 Sort interface for timestamp + implemention

Sort.hpp
```cpp
#ifndef EVENT_SORT_HPP
#define EVENT_SORT_HPP

#include "EventLog.hpp"

//sorting the log by timestamp using insertion
void insertionSortByTimestamp(EventLog* log);

//check if log is sorted by timestamp
bool isSortedByTimestamp(const EventLog* log);

#endif

```

Sort.cpp
```cpp
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
```


## Task 4 Event Loop (Producer/Consumer)

### 4.3 Testing integration with queue and log

```cpp
#include <iostream>
#include "include/Event.hpp"
#include "include/EventQueue.hpp"
#include "include/EventLog.hpp"
#include "include/EventLoop.hpp"

using namespace std;

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

    cout << "\nEventLog contents:\n";

    for (int i = 0; i < size; i++) {
        Event e = log_get(log, i);
        printEvent(e);
    }
}

int main() {
    Queue* queue = queue_create(5);
    EventLog* log = log_create(2);

    cout << "Running 5 event loop ticks...\n\n";

    eventLoop_runTicks(queue, log, 5);

    printLog(log);

    queue_destroy(queue);
    log_destroy(log);

    return 0;
    
}
```

### 4.2 EventLoop interface + implement producer/consumer tick
EventLoop.hpp
```cpp
#ifndef EVENT_LOG_HPP
#define EVENT_LOG_HPP

#include "Event.hpp"

using namespace std;

//ADT for storing events
//hidden struct
struct EventLog;

//creates new EventLog with startpoint/capacity
EventLog* log_create(int capacity);

//frees all memory used by Eventlog
void log_destroy(EventLog* log);

//returns number of events now being stored
int log_size(const EventLog* log);

//adds new events to the log
void log_append(EventLog* log, Event e);

//gets events at index
Event log_get(const EventLog* log, int index);


//replaces event at index
void log_set(EventLog* log, int index, Event e);

#endif
```

EventLoop.cpp
```cpp
//event producer
Event produceEvent() {
    static int nextSensorId = 1;
    
    EventType type;
    int value;

    //rotates between event types
    if (nextSensorId % 3 == 1) {
        type = TEMP;
        value = 20 + nextSensorId;
    } else if (nextSensorId % 3 == 2) {
        type = BUTTON;
        value = 1;
    }

    Event e = createEvent(nextSensorId, type, value);

    nextSensorId++;

    return e;
}

void eventLoop_tick(Queue* queue, EventLog* log) {
    if (queue == nullptr || log == nullptr) {
        cout << "Event loop error: queue or log is null.\n";
        return;
    }

    //tick flow
    Event produced = produceEvent();
     
    bool enqueued = queue_enqueue(queue, produced);

    if (!enqueued) {
        cout << "Queue is full. Event was dropped.\n";
        return;
    }

    Event consumed;

    bool dequeued = queue_dequeue(queue, &consumed);

    if (dequeued) {
        log_append(log, consumed);
        cout << "Processed event: "
             << "Timestamp: " << consumed.timestamp
             << ", Sensor ID: " << consumed.sensorId
             << ", Type: " << eventTypeToString(consumed.type)
             << ", Value: " << consumed.value
             << '\n';
    }
}
    void eventLoop_runTicks(Queue* queue, EventLog* log, int iterations) {
        if (iterations <= 0) {
            cout << "Number of ticks must be greater than 0.\n";
            return;
        }

        for (int i =0; i < iterations; i++) {
            eventLoop_tick(queue, log);
        }
    }
```



## Task 3 ADT: EventQueue (ring buffer)

### 3.3 Test Eventqueue behaviours
```cpp
void printEvent(const Event& e) {
    cout  << "Timestamp: " << e.timestamp
          << ", Sensor ID: " << e.sensorId
          << ", Type: " << eventTypeToString(e.type)
          << ", Value: " << e.value
          << '\n';
}

int main() {
    Queue* q = queue_create(3);

    cout << "Queue empty? " << (queue_isEmpty(q) ? "yes" : "no") << '\n';

    Event e1 = createEvent(1, TEMP, 25);
    Event e2 = createEvent(2, BUTTON, 1);
    Event e3 = createEvent(3, MOTION, 100);
    Event e4 = createEvent(4, TEMP, 30);

    cout <<"\nEnqueue e1: " << (queue_enqueue(q, e1) ? "success" : "failed") << '\n';
    cout <<"Enqueue e2: " << (queue_enqueue(q, e2) ? "success" : "failed") << '\n';
    cout <<"Enqueue e3: " << (queue_enqueue(q, e3) ? "success" : "failed") << '\n';

    cout << "Queue full? " << (queue_isFull(q) ? "yes" : "no") << "\n";

    cout << "Enqueue e4 into full queue: " << (queue_enqueue(q, e4) ? "success" : "failed") << '\n';

    Event out;

    cout << "\nDequeue 1:\n";
    if (queue_dequeue(q, &out)) {
        printEvent(out);
    }

    cout << "\nDequeue 2:\n";
    if (queue_dequeue(q, &out)) {
        printEvent(out);
    }

    cout << "\nEnqueue e4 after dequeing two events: " << (queue_enqueue(q, e4) ? "success" : "failed") << '\n';

    cout << "\nRemaining dequeue operations:\n";
    while (queue_dequeue(q, &out)) {
        printEvent(out);
    }

    cout << "\nQueue empty? " << (queue_isEmpty(q) ? "yes" : "no") << '\n';

    cout << "Try dequeue from empty queue: " << (queue_dequeue(q, &out) ? "success" : "failed") << '\n';

    queue_destroy(q);

    return 0;
}
```

### 3.2 Implement queue logic

```cpp
//struct, representing the queue
struct Queue {
    Event* buffer;
    int capacity;
    int head;
    int tail;
    int count;
};

//function to create a new queue
Queue* queue_create(int capacity) {
    if (capacity <= 0) {
        capacity = 1;
    }

    Queue* q = new Queue;
    q->buffer = new Event[capacity];
    q-> capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->count = 0;

    return q;
}

//function  to destroy a queue
void queue_destroy(Queue* q) {
    if (q == nullptr) {
        return;
    }

    delete[] q->buffer;
    delete q;
}

//check if the queue is empty
bool queue_isEmpty(const Queue* q) {
    if (q == nullptr) {
        return true;
    }

    return q->count == 0;
}

//check if the queue is full
bool queue_isFull(const Queue* q) {
    if (q == nullptr) {
        return false;
    }

    return q->count == q->capacity;
}

//function to add an event to the queue 
bool queue_enqueue(Queue* q, Event e){
    if (q == nullptr) {
        return false;
    }

    if (queue_isFull(q)) {
        return false;
    }

    q->buffer[q->tail] = e;
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;

    return true;
}

//function to remove an event from the queue
bool queue_dequeue(Queue* q, Event* out) {
    if (q == nullptr || out == nullptr) {
        return false;
    }

    if (queue_isEmpty(q)) {
        return false;
    }

    *out = q->buffer[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->count--;

    return true;
}
```

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