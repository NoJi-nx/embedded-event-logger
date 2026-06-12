#include "EventLoop.hpp"
#include <iostream>

using namespace std;

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
    } else {
        type = MOTION;
        value = 100;
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