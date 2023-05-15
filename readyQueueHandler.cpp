/*
readyQueueHandler.cpp
Manages ready queue
*/

#include "readyQueueHandler.h"

void addProcessToReadyQueue(const Process process, std::vector<Process> &ReadyQueue){
    ReadyQueue.push_back(process);
}