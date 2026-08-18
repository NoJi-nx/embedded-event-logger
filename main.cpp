#include <iostream>
#include "include/EventQueue.hpp"
#include "include/EventLog.hpp"
#include "include/Menu.hpp"
#include "include/AlarmSet.hpp"

using namespace std;


//main function 
int main() {
    Queue* queue = queue_create(10);
    EventLog* log = log_create(10);
    AlarmSet* alarms = alarm_create(20, 30);
    LatestEventStore* latestStore = latest_create(100);

    runCommandMenu(queue, log, alarms, latestStore);

    latest_destroy(latestStore);
    alarm_destroy(alarms);
    queue_destroy(queue);
    log_destroy(log);


    return 0;

}