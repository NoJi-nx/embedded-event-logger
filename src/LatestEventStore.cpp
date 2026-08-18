#include "LatestEventStore.hpp"
#include <iostream>


using namespace std;

//struct for storing latest events each sensor
struct LatestEventStore {
    Event* latestEvents;
    bool* hasEvent;
    int maxSensorId;
};

//function to create a new latest event store
LatestEventStore* latest_create(int maxSensorId) {
    if (maxSensorId < 0) {
        maxSensorId = 0;
    }

    LatestEventStore* store = new LatestEventStore;

    store->latestEvents = new Event[maxSensorId + 1];
    store->hasEvent = new bool[maxSensorId + 1];
    store->maxSensorId = maxSensorId;

    for (int i = 0; i <= maxSensorId; i++) {
        store->hasEvent[i] = false;
    }

    return store;
}

//destroy a latest event store
void latest_destroy(LatestEventStore* store) {
    if (store == nullptr) {
        return;
    }        

        delete[] store->latestEvents;
        delete[] store->hasEvent;
        delete store;
    }
    
//update the latest event for a sensor
bool latest_updateFromEvent(LatestEventStore* store, const Event& e) {
    if (store == nullptr) {
        return false;
    }

    if (e.sensorId < 0 || e.sensorId > store->maxSensorId) {
        cout << "LatestEventStore: sensor ID"
        << e.sensorId 
        << " is outside supported range.\n";

        return false;
    }

    store->latestEvents[e.sensorId] = e;
    store->hasEvent[e.sensorId] = true;
    return true;

}

//get the latest event for a sensor
bool latest_get(const LatestEventStore* store, int sensorId, Event* out) {
    if (store == nullptr || out == nullptr) {
        return false;
    }

    if (sensorId < 0 || sensorId > store->maxSensorId) {
        return false;
    }

    if(!store->hasEvent[sensorId]) {
        return false;
    }

    *out = store->latestEvents[sensorId];
    return true;
}

//print the latest event for a sensor
void latest_print(const LatestEventStore* store, int sensorId) {
    Event e;

    if(!latest_get(store, sensorId, &e)) {
        cout << "No latest event found for sensor ID "
            << sensorId << ".\n";
            
            return;
    }

    cout << "Latest event for sensor ID " << sensorId << ":\n";
    cout << "Timestamp: " << e.timestamp
         << ", Sensor ID: " << e.sensorId
         << ", Type: " << eventTypeToString(e.type)
         << ", Value: " << e.value
         << '\n';
}


