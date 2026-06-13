#include <iostream>
#include "include/EventQueue.hpp"
#include "include/EventLog.hpp"
#include "include/Menu.hpp"

using namespace std;


//main function 
int main() {
    Queue* queue = queue_create(10);
    EventLog* log = log_create(10);

    runCommandMenu(queue, log);

    queue_destroy(queue);
    log_destroy(log);

    return 0;

}