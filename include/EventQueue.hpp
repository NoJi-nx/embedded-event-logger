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

