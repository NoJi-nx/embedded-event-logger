# Embedded-event-logger
Program that recieves incoming events, stores prcoessed events &amp; processes events and interacts with the user


Github repo:
https://github.com/NoJi-nx/embedded-event-logger

### Build

Use the configured build task:

```
Cmd + Shift + B
```

Build the program and creates the following file:

*event_logger*


### Run

After building, run:
```
./event_logger
```
<br>

## Commands

### Show help
```help```

Show available commands

### Run event loop ticks

```
tick[n]
tick 5 
tick 10
```

Run one or more event loop ticks, depending on the amount.


### Print all logged events

```print```

Print all events in the log



### Search events by sensor ID

```
find [sensorId]
find 1
find 2
```

Find all events from a selected sensor


### Sort the log

```
sort insertion
sort selection
```

The sorting algorithm. One sort log by timestamp using insetion, the other sort log using selection sort.

### Show active alarms

```alarms```

Show active temperature alarms. This prints sensors currentyl above the temperature threshold

### Set temperature threshold

```
set-threshold 25
set-threshold 30
```
Show active temperature alarms
Temperature events above the threshold activates and alarm

### Show latest event for a sensor

```
last [sensorId]
last 1
last 2
```

Show latest event for a sensor. It retrieves the latest processed event for the selected sensor using the fast lookup.


### Exit program

```exit```

Exit the program


## Project Flow

```
Producer -> EventQueue -> EventLoop -> EventLog
```

During each tick

* **Event** is produced
* **Events** is added to the queue
* **Event** is stored in the log
* **AlarmSet** is updated
* **LatestEventStore** is updated

## Notes

Timestamps are generated in increasing order which makes the event log already appear sorted. Both insertion and selection sort should produce the same final order because both sort by the timestamp. The difference is in. how the algorithms work.


