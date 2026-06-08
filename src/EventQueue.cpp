#include "EventQueue.hpp"
#include <iostream>

struct Queue {
    Event* buffer;
    int capacity;
    int head;
    int tail;
    int count;
};

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

void queue_destroy(Queue* q) {
    if (q == nullptr) {
        return;
    }

    delete[] q->buffer;
    delete q;
}

bool queue_isEmpty(const Queue* q) {
    if (q == nullptr) {
        return true;
    }

    return q->count == 0;
}

bool queue_isFull(const Queue* q) {
    if (q == nullptr) {
        return false;
    }

    return q->count == q->capacity;
}

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