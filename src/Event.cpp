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