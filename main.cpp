#include <iostream>
#include "include/Event.hpp"
#include "include/EventLog.hpp"

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

