/*
readyQueueHandler.h
Manages ready queue
*/

#ifndef READYQUEUEHANDLER_H
#define READYQUEUEHANDLER_H

#include "processHandler.h"
#include <vector>


void addProcessToReadyQueue(const Process process, std::vector<Process> &ReadyQueue);

#endif /* READYQUEUEHANDLER_H */