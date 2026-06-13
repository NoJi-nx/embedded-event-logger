#include "Menu.hpp"
#include "Event.hpp"
#include "EventLoop.hpp"
#include "Sort.hpp"
#include "Search.hpp"
#include "SortStrategy.hpp"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//print details of a single event
static void printEvent(const Event& e) {
    cout  << "Timestamp: " << e.timestamp
          << ", Sensor ID: " << e.sensorId
          << ", Type: " << eventTypeToString(e.type)
          << ", Value: " << e.value
          << '\n';
}

//print all the events in the log
void printLog(const EventLog* log) {
    int size = log_size(log);

    if (size == 0) {
        cout << "Log is empty.\n";
        return;
    }

    cout << "\nEventLog contents:\n";

    for (int i = 0; i < size; i++) {
        Event e = log_get(log, i);
        printEvent(e);
    }
}

// function that shows command menu
static void printHelp() {
    cout << "\nAvailable commands: \n";
    cout << " tick [n]               Run n event loop ticks. Default is 1.\n";
    cout << " print                  Print all events in the log.\n";
    cout << " sort [strategy]        Sort log by timestamp. Default: insertion.\n";
    cout << "                        Available: insertion.\n";    
    cout << " find <id>              Find events by sensor ID.\n";
    cout << " help                   Show help message.\n";
    cout << " exit                   Exit the program.\n\n";
}



//run the command menu
void runCommandMenu(Queue* queue, EventLog* log) {
    if (queue == nullptr || log == nullptr) {
        cout << "Command menu error: queue or log is null.\n";
        return;
    }

    string line;

    cout << "Event logger\n";
    cout << "Type 'help' to see available commands.\n";

    while (true) {
        cout << "\n> ";
        getline(cin, line);

        stringstream ss(line);

        string command;
        ss >> command;

        if (command == "tick") {
            int iterations = 1;

            if (ss >> iterations) {
                eventLoop_runTicks(queue, log, iterations);

            } else {
                eventLoop_runTicks(queue, log, 1);
            }
        }

        else if (command == "print") {
            printLog(log);
        }

        else if (command == "sort") {
           string strategyName;

           if (!(ss >> strategyName)) {
            strategyName = "insertion";
           }

           bool success = sortLogWithStrategy(log, strategyName);

           if (!success) {
            cout << "Unknown sorting strategy: " << strategyName << '\n';
            cout << "Available strategies: insertion\n";
            continue;
           }

           cout << "Log sorted by timestamp using " << strategyName << " sort.\n";

           if (isSortedByTimestamp(log)) {
            cout << "Sort check: log is sorted.\n";
           } else {
            cout << "Sort check: log is not sorted. \n";
           }
        }
        

        else if (command == "find") {
            int sensorId;

            if (ss >> sensorId) {
                int matches = findEventsBySensorId(log, sensorId);
                cout << "Matches found: " << matches << '\n';
            } else {
                cout << "Usage: find <sensorId>\n";
            }
        } 

        else if (command == "help") {
            printHelp();
        }

        else if (command == "exit") {
            cout << "Exiting Event Logger.\n";
            break;
        }

        else {
            cout << "Unknown command: " << command << '\n';
            cout << "Type 'help' to see available commands.\n";
        }

        } 
    }