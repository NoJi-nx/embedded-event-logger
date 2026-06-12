#include "EventQueue.hpp"
#include <iostream>

using namespace std;

//struct, representing the queue
struct Queue {
    Event* buffer;
    int capacity;
    int head;
    int tail;
    int count;
};

//function to create a new queue
Queue* queue_create(int capacity) {
    if (capacity <= 0) {
        capacity = 1;
    }

    Queue* q = new Queue;
    q->buffer = new Event[capacity];
    q-> capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->count = 0;

    return q;
}

//function  to destroy a queue
void queue_destroy(Queue* q) {
    if (q == nullptr) {
        return;
    }

    delete[] q->buffer;
    delete q;
}

//check if the queue is empty
bool queue_isEmpty(const Queue* q) {
    if (q == nullptr) {
        return true;
    }

    return q->count == 0;
}

//check if the queue is full
bool queue_isFull(const Queue* q) {
    if (q == nullptr) {
        return false;
    }

    return q->count == q->capacity;
}

//function to add an event to the queue 
bool queue_enqueue(Queue* q, Event e){
    if (q == nullptr) {
        return false;
    }

    if (queue_isFull(q)) {
        return false;
    }

    q->buffer[q->tail] = e;
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;

    return true;
}

//function to remove an event from the queue
bool queue_dequeue(Queue* q, Event* out) {
    if (q == nullptr || out == nullptr) {
        return false;
    }

    if (queue_isEmpty(q)) {
        return false;
    }

    *out = q->buffer[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->count--;

    return true;
}