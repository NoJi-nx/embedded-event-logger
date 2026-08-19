# Report

- Overview
- Design pattern: Strategy-light
- Time Complexity
- Memory Management


## Overview

The project is a small simulator for an embedded logger. The system not only creates sensor events,but also places them in a queue, processe them through an event loop, and stored them in a log. Each event contains a sensor ID, event type, timestamp and value.
The program flow works like this: <br>
Producer -> EventQueue -> EventLoop -> EventLog
When a tick runs, an event is produced, enqueued & dequeed, processed and added/appended to the log. The optional modules are AlarmSet & LatestEventstore. The former check temperature alarms and the latter updattes the latest event. for the event's sensor ID.

## Design pattern: Strategy-light

The project includes a Strategy-light pattern for sorting as a usage.  A function pointer type is used:

using SortFn = void (*)(EventLog* log);

Both sorting algorithms have same function signature
- **void insertiomSortbyTimestamp(EventLog* log);**
- **void selectionSortByTimestamp(EventLog* log);**

The module **SortStrategy** maps a command string to the right sorting function

- "insertion" -> insertionSortByTimestamp
- "selection" -> selectionSortByTimestamp


It allows to run in the command menu to choose which sorting style: **sort insertion** or **sort selection**.
The design makes it easier to add more sorting algorithms because each new algorithm only needs the same function signature and a new entry in the strategy selector.

## Time Complexity

The **EventQueue** is implented as a ring buffer. Enqueue and dequeue are both **0(1)**. With this, the operations on the queue are efficient.
Searching by sensor ID uses linear search through the **EventLog**. With it, the command **find <sensorId>** has time complexity 0(n), where n is the number of events in the log.

Command **last <sensorId>** uses LatestEventStore, storing events in an array losted by sensor ID. It gives direct lookup in **0(1)** time but uses extra memory.
As said, sorting is implemented with inserion and selection sort. Both algorithms sort tthe log by timestamp. Insertion sort has complexity 0(n^2) and can be 0(n) if the log is already sorted. Selection has 0(n^2) complexity in all cases, due to it scanning for the smallest element repeatedly.


## Memory Management

The project uses manual memory managmenet with **new**, **new[]**, **delete** and **delete[]**. <br>
Memory is allocated in create functions such as log_create, queue_create, alarm_create & latest_create.<br>
It also released om the matching destroy functions such as **log_destroy**, **queue_destroy**, **alarm_destroy** ,**latest_destroy**. <br>
With this structure, it helps avoid memory leaks because every module thatt allocates memory also provides a function to free it. In **main.cpp**, all created ADTs interfaces are destroyed before the program exits. The internal arrays are hidden inside their modules, so other parts of the program use public functions instead of accessing or freeing internal memory.