#ifndef LATEST_EVENT_STORE_HPP
#define LATEST_EVEBT_STORE_HPP

#include "Event.hpp"


struct LatestEventStore;


//creating store that supportts sensor Ids from 0 to maxSensorId
LatestEventStore* latest_create(int maxSensorId);

//frees memory
void latest_destroy(LatestEventStore* store);

//updates the latest event for the event's sensor Id
bool latest_updateFromEvent(LatestEventStore* store, const Event& e);

//get latest event for a sensor & returns false if no event exists or invalid sensorId
bool latest_get(const LatestEventStore* store, int sensorId, Event* out);

//prints latest event for a sensor
void latest_print(const LatestEventStore* store, int sensorId);

#endif 