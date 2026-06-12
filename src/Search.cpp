#include "Search.hpp"
#include "Event.hpp"
#include <iostream>

using namespace std;


//function to print found events
static void printFoundEvent(const Event&& e) {
    cout << "Timestamp: " << e.timestamp
         << ", Sensor ID: " << e.sensorId
         << ", Type: " << eventTypeToString(e.type)
         << ", Value: " << e.value
         << '\n';

}

//function to find events by given sensor Id
int findEventsBySensorId(const EventLog* log, int sensorId) {
    if (log == nullptr) {
        cout << "Search error: log is null.\n";
        return 0;
    }

    int size = log_size(log);
    int matches = 0;

    for (int i = 0; i < size; i++) {
        Event e = log_get(log, i);

        if (e.sensorId == sensorId) {
            printFoundEvent(e);
            matches++;
        }
    }

    if (matches == 0) {
        cout << "No events found for sensor ID " << sensorId << ".\n";
    }

    return matches;
}