#include <iostream>
#include "include/Event.hpp"
#include "include/EventQueue.hpp"
#include "include/EventLog.hpp"
#include "include/EventLoop.hpp"
#include "include/Sort.hpp"
#include "include/Search.hpp"

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
    //Queue* queue = queue_create(5);
    EventLog* log = log_create(2);

    Event e1 = createEvent(1, TEMP, 25);
    Event e2 = createEvent(2, BUTTON, 1);
    Event e3 = createEvent(1, TEMP, 30);
    Event e4 = createEvent(3, MOTION, 100);
    Event e5 = createEvent(2, TEMP, 28);

    log_append(log, e1);
    log_append(log, e2);
    log_append(log, e3);
    log_append(log, e4);
    log_append(log, e5);

    printLog(log);

    cout << "\nSearching for sensor ID 1:\n";
    int match1 = findEventsBySensorId(log, 1);
    cout << "Matches found: " << match1 << "\n";

    cout << "\nSearching for sensor ID 2:\n";
    int match2 = findEventsBySensorId(log, 2);
    cout << "Matches found: " << match2 << "\n";

    cout << "\nSearching for sensor ID 3:\n";
    int match3 = findEventsBySensorId(log, 3);
    cout << "Matches found: " << match3 << "\n";

    cout << "\nSearching for sensor ID 10:\n";
    int match10 = findEventsBySensorId(log, 10);
    cout << "Matches found: " << match10 << "\n";
    log_destroy(log);
    
    
    //empty log test - Search task
    EventLog* emptyLog = log_create(2);

    cout << "\nSearching empty log:\n";
    int emptyMatch = findEventsBySensorId(emptyLog, 1);
    cout << "Matches found: " << emptyMatch << "\n";
    log_destroy(emptyLog);


    //one-element log - Search task
    EventLog* oneLog = log_create(2);

    log_append(oneLog, createEvent(7, TEMP, 22));

    cout << "\nSearching one-element log for sensor ID 7:\n";
    int oneMatch = findEventsBySensorId(oneLog, 7);
    cout << "Matches found: " << oneMatch << "\n";
    log_destroy(oneLog);

    return 0;


    
}


/*
    cout <<"Before sorting:\n";
    printLog(log);

    cout << "\nIs sorted? "
         << (isSortedByTimestamp(log) ? "yes" : "no")
         << '\n';
     
    insertionSortByTimestamp(log); 

    cout << "\nAfter sorting:\n";
    printLog(log);

    cout << "\nIs sorted? "
         << (isSortedByTimestamp(log) ? "yes" : "no")
         << '\n';

    log_destroy(log);

    return 0;

    */

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