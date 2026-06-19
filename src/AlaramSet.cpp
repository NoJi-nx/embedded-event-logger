#include "AlarmSet.hpp"
#include <iostream>

using namespace std;


//struct to represent an alarm set
struct AlarmSet {
    int* sensorIds;
    int count;
    int capacity;
    int threshold;
};


//creating Alarmset with fixed capacity and starting threshold
AlarmSet* alarm_create(int capacity, int threshold) {
    if (capacity <= 0) {
        capacity = 1;
    }

    AlarmSet* alarms = new AlarmSet;
    alarms->sensorIds = new int[capacity];
    alarms->count = 0;
    alarms->capacity = capacity;
    alarms->threshold = threshold;

    return alarms;
}

//function to free memory
void alarm_destroy(AlarmSet* alarms) {
    if (alarms == nullptr) {
        return;
    }

    delete[] alarms->sensorIds;
    delete alarms;
}

//function to get threshold
int alarm_getThreshold(const AlarmSet* alarms) {
    if (alarms == nullptr) {
        return 0;
    }

    return alarms->threshold;
}

//function to set threshold
void alarm_setThreshold(AlarmSet* alarms, int threshold) {
    if (alarms == nullptr) {
        return;
    }

    alarms->threshold = threshold;
}

//function to check if sensor is in alarm set
bool alarm_contains(const AlarmSet* alarms, int sensorId) {
    if (alarms == nullptr) {
        return false;
    }

    for (int i = 0; i < alarms->count; i++) {
        if (alarms->sensorIds[i] == sensorId) {
            return true;
        }
    }

    return false;
}

//function to add sensor to alarm set
bool alarm_add(AlarmSet* alarms, int sensorId) {
    if(alarms == nullptr) {
        return false;
    }

    if (alarm_contains(alarms, sensorId)) {
        return true;
    }

    if (alarms->count == alarms->capacity) {
        cout << "AlarmSet is full. Could not add sensor "
             << sensorId << ".\n";

        return false;     
    }

    alarms->sensorIds[alarms->count] = sensorId;
    alarms->count++;

    return true;

}

//function to remove sensor from alarm set
bool alarm_remove(AlarmSet* alarms, int sensorId) {
    if (alarms == nullptr) {
        return false;
    }

    for (int i =0; i < alarms->count; i++) {
        if (alarms->sensorIds[i] == sensorId) {
            alarms->sensorIds[i] = alarms->sensorIds[alarms->count - 1];
            alarms->count--;
            return true;
        }
    }

    return false;
}

//function to update alarm set based on event
void alarm_updateFromEvent(AlarmSet* alarms, const Event& e) {
    if (alarms == nullptr) {
        return;
    }

    if (e.type != TEMP) {
        return;
    }

    if (e.value > alarms->threshold) {
        bool wasAlreadyActive = alarm_contains(alarms, e.sensorId);
        alarm_add(alarms, e.sensorId);

        if (!wasAlreadyActive) {
            cout << "ALARM ON_ sensor " << e.sensorId
                 << " temperature " << e.value
                 << " > threshold " << alarms->threshold << '\n';
        }
    } else {
        bool wasActive = alarm_contains(alarms, e.sensorId);
        alarm_remove(alarms, e.sensorId);

        if (wasActive) {
            cout << "ALARM OFF: sensor " << e.sensorId
                 << " temperature " << e.value
                 << " <= threshold " << alarms->threshold << '\n';
        }
    }
}

//function to print all active alarms
void alarm_print(const AlarmSet* alarms) {
    if (alarms == nullptr) {
        cout << "Alarm error: AlarmSet is null.\n";
        return;
    }

    cout <<"Temperature threshold: "
         << alarms->threshold << '\n';
    
    if (alarms->count == 0) {
        cout << "No active alarms.\n";
        return;
    }
    
    cout << "Active alarms:\n";

    for (int i = 0; i < alarms->count; i++) {
        cout << "Sensor ID: " << alarms->sensorIds[i] << '\n';
    }
}