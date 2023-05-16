/*
displayHandler.h
print information to the console
*/

#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <list>
#include <vector>
#include "processHandler.h"
#include "jobHandler.h"
#include "deviceHandler.h"

// The following function is used to handle display events.
void handle_display_event(
    int time, 
    Process CPU,
    SortedLinkedList HoldQueue1, 
    SortedLinkedList HoldQueue2,
    std::vector<Process> ReadyQueue, 
    std::vector<Job> jobs, 
    std::vector<Process> CompleteQueue
);

#endif /* DISPLAYHANDLER_H */