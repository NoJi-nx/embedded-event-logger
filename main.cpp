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


/* void printLog(const EventLog* log) {
    int size = log_size(log);

    if (size == 0) {
        cout << "Log is empty.\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        Event e = log_get(log, i);
        printEvent(e);
    }
}*/

/*
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
*/


/*
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
    */